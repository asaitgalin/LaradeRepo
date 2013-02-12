using System;
using System.IO;

interface IFileProcessor
{
    long ProcessFile(string path);
}

class FileProcessor : IFileProcessor
{
    private SQLFileWorker worker;

    public FileProcessor()
    {
        worker = new SQLFileWorker();
    }

    public long ProcessFile(string path)
    {
        FileInfo fi = new FileInfo(path);
        long size = fi.Length;
        long fileHash = Hasher.HashFile(path);
        long pathHash = Hasher.HashPath(path);
        string fileName = Path.GetFileName( path );
        string extension = Path.GetExtension( path );
        
        long id = worker.Insert(fileHash, pathHash, path, fileName, extension, size);
        return id;
    }
}

class Au : FileProcessor
{
    
}