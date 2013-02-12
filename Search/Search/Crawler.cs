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

    public virtual long ProcessFile(string path)
    {
        FileInfo fi = new FileInfo(path);
        long size = fi.Length;
        long fileHash = Hasher.HashFile(path);
        long pathHash = Hasher.HashPath(path);

        BaseFileInfo fileInfo = new BaseFileInfo(fileHash, pathHash, path, size);

        long id = worker.Insert( fileInfo );
        return id;
    }
}

class AudioFileProcessor : FileProcessor
{
    public override long ProcessFile( string path )
    {
        return base.ProcessFile( path );
    }
}