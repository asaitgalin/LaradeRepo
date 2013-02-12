using System;
using System.Collections.Generic;
using System.IO;

interface IFileProcessor
{
    long ProcessFile(FileInfo info);
}

class FileProcessor : IFileProcessor
{
    private SQLFileWorker worker;

    public FileProcessor()
    {
        worker = new SQLFileWorker();
    }

    public virtual long ProcessFile(FileInfo info)
    {
        long id = -1;
        int i=0;
        for(;;)
        {
            long pathHash = Hasher.HashPath( info.FullName );
            id = worker.FindByPathHash(pathHash);
            if ( id != -1 )
                break;

            long fileHash = Hasher.HashFile(info.FullName);
            id = worker.FindByFileHash( fileHash );
            if ( id != -1 )
            {
                worker.InsertFolderInfo(id, info.FullName);
                break;
            }

            long size = info.Length;
            BaseFileInfo fileInfo = new BaseFileInfo(fileHash, pathHash, info.FullName, size);
            id = worker.Insert( fileInfo );
            break;
        }
        return id;
    }
}

class AudioFileProcessor : FileProcessor
{
    public override long ProcessFile( FileInfo info )
    {
        return base.ProcessFile( info );
    }
}

class Crawler
{
    protected IFileProcessor Processor;
    protected string InitDirectory;

    public Crawler(IFileProcessor fileProc, string initDirectory)
    {
        Processor = fileProc;
        InitDirectory = initDirectory;
    }

    public void DoWork()
    {
        ScanDirectory(new DirectoryInfo(InitDirectory));
    }

    private void ScanDirectory(DirectoryInfo directory)
    {
        foreach(var file in directory.GetFiles())
        {
            Processor.ProcessFile(file);
        }

        foreach(var dir in directory.GetDirectories())
        {
            ScanDirectory(dir);
        }
    }
}