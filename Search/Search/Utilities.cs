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
        byte[] buff = new byte[1024 * 512];        
        byte[] hashValue;
        using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
        {
            fs.Read(buff, 0, buff.Length);
            fs.Close();
        }
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
    public const string filePathsTable       =   "FilePaths";
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
    long FileHash;
    long PathHash;
    string Path;
    string Name
    {
        get 
        {
            return System.IO.Path.GetFileName(Path);
        }
    }
    string Extension 
    {
        get
        {
            return System.IO.Path.GetExtension(Path);
        }
    }
    long Size;

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
    protected SqlCommand InsertPathCmd;

    public SQLFileWorker()
    {
        string query = String.Format(
            "INSERT INTO {0}   (pathHash, fileHash, name, extension, size) " + 
            "VALUES (@pathHash, @fileHash, @name, (SELECT ID FROM {1} WHERE extension = @extension), @size);" +
            "SELECT SCOPE_IDENTITY()",
            SQLSettings.filesTable, SQLSettings.extensionTable);
        InsertCmd = new SqlCommand( query, connect );
        InsertCmd.Parameters.Add( "@pathHash", System.Data.SqlDbType.BigInt );
        InsertCmd.Parameters.Add( "@fileHash", System.Data.SqlDbType.BigInt );
        InsertCmd.Parameters.Add( "@name", System.Data.SqlDbType.NVarChar );
        InsertCmd.Parameters.Add( "@extension", System.Data.SqlDbType.NVarChar);
        InsertCmd.Parameters.Add( "@size", System.Data.SqlDbType.BigInt );

        query = String.Format("INSERT INTO {0} (id, filePath) VALUES (@id, @filePath)", SQLSettings.filePathsTable);
        InsertPathCmd = new SqlCommand( query, connect );
        InsertPathCmd.Parameters.Add("@id", System.Data.SqlDbType.Int);
        InsertPathCmd.Parameters.Add("@filePath", System.Data.SqlDbType.NVarChar);
    }

    public long Insert(long fileHash, long pathHash, string path, string fileName, string extension, long size)
    {
        CheckExtension(extension);

        InsertCmd.Parameters["@pathHash"].Value = pathHash;
        InsertCmd.Parameters["@fileHash"].Value = fileHash;
        InsertCmd.Parameters["@name"].Value = fileName;
        InsertCmd.Parameters["@extension"].Value = extension;
        InsertCmd.Parameters["@size"].Value = size;
        reader = InsertCmd.ExecuteReader();

        reader.Read();
        string id = reader[0].ToString();
        reader.Close();

        InsertPathCmd.Parameters["@id"].Value = id;
        InsertPathCmd.Parameters["@filePath"].Value = path;
        InsertPathCmd.ExecuteNonQuery();
        return long.Parse(id);
    }

    private void CheckExtension(string extension)
    {
        string query = String.Format(
            "UPDATE {0} SET extension = @extension WHERE extension = @extension " + 
            "IF @@ROWCOUNT = 0 INSERT INTO {0} (extension) VALUES (@extension)", 
            SQLSettings.extensionTable);
        SqlCommand tempCmd = new SqlCommand(query, connect);
        tempCmd.Parameters.Add("@extension", System.Data.SqlDbType.NVarChar);
        tempCmd.Parameters["@extension"].Value = extension;
        tempCmd.ExecuteNonQuery();
    }
}