using System;
using System.Security.Cryptography;
using System.IO;
using System.Text;
using System.Data.SqlClient;

class Hasher
{
    private static SHA256 mySHA256 = SHA256Managed.Create();

    public static long HashFile(string path)
    {
        byte[] name = Encoding.Default.GetBytes( Path.GetFileName( path ) );
        byte[] buff = new byte[1024 * 512 + name.Length];
        byte[] hashValue;
        int bytesCount = 0;
        using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
        {
            if (fs.Length < 512 * 1024)
            {
                bytesCount = fs.Read( buff, 0, 1024 * 512 );
            }
            else
            {
                fs.Read(buff, 0, 128 * 1024);
                fs.Seek(fs.Length / 2 - 128 * 1024, SeekOrigin.Begin);
                fs.Read(buff, 128 * 1024, 256 * 1024);
                fs.Seek(-128 * 1024, SeekOrigin.End);
                fs.Read(buff, 384 * 1024, 128 * 1024);
                bytesCount = 1024 * 512;
            }
            fs.Close();
        }
        Array.Copy(name, 0, buff, bytesCount, name.Length); 
        hashValue = mySHA256.ComputeHash(buff);
        return BitConverter.ToInt64(hashValue, 0);
    }

    public static long HashPath(string path)
    {
        byte[] buff = Encoding.Default.GetBytes(path);
        byte[] hashValue = mySHA256.ComputeHash(buff);
        return BitConverter.ToInt64(hashValue, 0);
    }
}

class SQLSettings
{
    public const string Server               =   "LAPTOP\\SQLEXPRESS";
    public const string Database             =   "MIPTSearch";
    public const string filesTable           =   "Files";
    public const string extensionTable       =   "Extensions";
    public const string filePathsTable       =   "Folders";
    public const string locationsTable       =   "Locations";
}

class SQLWorkerBase
{
    protected SqlConnection connect;
    protected SqlDataReader reader;
    protected string connectionString;

    public SQLWorkerBase()
    {
        connectionString = String.Format(   "Server = {0}; Database = {1}; Trusted_Connection=True;", 
                                            SQLSettings.Server, SQLSettings.Database );
        connect = new SqlConnection(connectionString);
        connect.Open();
    }
}

struct BaseFileInfo
{
    public long FileHash;
    public long PathHash;
    public string Path;
    public string Name
    {
        get 
        {
            return System.IO.Path.GetFileName(Path);
        }
    }
    public string Extension 
    {
        get
        {
            return System.IO.Path.GetExtension(Path);
        }
    }
    public long Size;

    public BaseFileInfo(long fileHash, long pathHash, string path, long size)
    {
        FileHash = fileHash;
        PathHash = pathHash;
        Path = path;
        Size = size;
    }
}

class SQLFileWorker : SQLWorkerBase 
{
    protected SqlCommand InsertCmd;

    public SQLFileWorker()
    {
        string query = String.Format(
            "INSERT INTO {0}   (pathHash, fileHash, name, extension, size) " + 
            "VALUES (@pathHash, @fileHash, @name, " + 
            "(SELECT ID FROM {1} WHERE extension = @extension), @size);" +
            "SELECT SCOPE_IDENTITY()",
            SQLSettings.filesTable, SQLSettings.extensionTable, SQLSettings.filePathsTable);
        InsertCmd = new SqlCommand( query, connect );
        InsertCmd.Parameters.Add( "@pathHash", System.Data.SqlDbType.BigInt );
        InsertCmd.Parameters.Add( "@fileHash", System.Data.SqlDbType.BigInt );
        InsertCmd.Parameters.Add( "@name", System.Data.SqlDbType.NVarChar );
        InsertCmd.Parameters.Add("@folderPath", System.Data.SqlDbType.NVarChar);
        InsertCmd.Parameters.Add( "@extension", System.Data.SqlDbType.NVarChar);
        InsertCmd.Parameters.Add( "@size", System.Data.SqlDbType.BigInt );
    }

    public long Insert(BaseFileInfo fi)
    {
        CheckExtension(fi.Extension);

        string parent = Directory.GetParent(fi.Path).FullName;

        InsertCmd.Parameters["@pathHash"].Value = fi.PathHash;
        InsertCmd.Parameters["@fileHash"].Value = fi.FileHash;
        InsertCmd.Parameters["@name"].Value = fi.Name;
        InsertCmd.Parameters["@folderPath"].Value = parent;
        InsertCmd.Parameters["@extension"].Value = fi.Extension;
        InsertCmd.Parameters["@size"].Value = fi.Size;
        long id = long.Parse(InsertCmd.ExecuteScalar().ToString());
        InsertFolderInfo(id, fi.Path);

        return id;
    }

    public void InsertFolderInfo(long id, string filePath)
    {
        CheckFolder(filePath);
        string folder = Directory.GetParent(filePath).FullName;
        string query = String.Format(   "INSERT INTO {0} (id, folderId) VALUES (@id, (SELECT id FROM Folders WHERE path = @folderPath))", 
                                        SQLSettings.locationsTable);
        SqlCommand tempCmd = new SqlCommand(query, connect);
        tempCmd.Parameters.Add("@id", System.Data.SqlDbType.BigInt);
        tempCmd.Parameters.Add("@folderPath", System.Data.SqlDbType.NVarChar);
        tempCmd.Parameters["@id"].Value = id;
        tempCmd.Parameters["@folderPath"].Value = folder;
        tempCmd.ExecuteNonQuery();
    }

    public long FindByFileHash(long Hash)
    {
        string query = String.Format("SELECT ID FROM {0} WHERE fileHash = @fileHash", SQLSettings.filesTable);
        SqlCommand selectCmd = new SqlCommand(query, connect);
        selectCmd.Parameters.Add("@fileHash", System.Data.SqlDbType.BigInt);
        selectCmd.Parameters["@fileHash"].Value = Hash;
        reader = selectCmd.ExecuteReader();
        long result = -1;
        if (reader.Read())
            result = long.Parse(reader[0].ToString());
        reader.Close();
        return result;
    }

    public long FindByPathHash(long Hash)
    {
        string query = String.Format( "SELECT ID FROM {0} WHERE fileHash = @pathHash", SQLSettings.filesTable );
        SqlCommand selectCmd = new SqlCommand( query, connect );
        selectCmd.Parameters.Add( "@pathHash", System.Data.SqlDbType.BigInt );
        selectCmd.Parameters["@pathHash"].Value = Hash;
        reader = selectCmd.ExecuteReader();
        long result = -1;
        if (reader.Read())
            result = long.Parse(reader[0].ToString());
        reader.Close();
        return result;
    }

    private void CheckExtension(string extension)
    {
        string query = String.Format(
            "SELECT 1 FROM {0} WHERE extension = @extension " + 
            "IF @@ROWCOUNT = 0 INSERT INTO {0} (extension) VALUES (@extension)", 
            SQLSettings.extensionTable);
        SqlCommand tempCmd = new SqlCommand(query, connect);
        tempCmd.Parameters.Add("@extension", System.Data.SqlDbType.NVarChar);
        tempCmd.Parameters["@extension"].Value = extension;
        tempCmd.ExecuteNonQuery();
    }

    private void CheckFolder(string path)
    {
        string parent = Directory.GetParent(path).FullName;
        string query = String.Format(
            "SELECT 1 FROM {0} WHERE path = @folderPath " +
            "IF @@ROWCOUNT = 0 INSERT INTO {0} (path) VALUES (@folderPath);",
            SQLSettings.filePathsTable);
        SqlCommand tempCmd = new SqlCommand(query, connect);
        tempCmd.Parameters.Add("@folderPath", System.Data.SqlDbType.NVarChar);
        tempCmd.Parameters["@folderPath"].Value = parent;
        tempCmd.ExecuteNonQuery();
        //return (long)tempCmd.ExecuteScalar();
    }
}