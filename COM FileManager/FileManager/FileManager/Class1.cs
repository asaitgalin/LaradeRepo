using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace FileManager
{
    interface IFSObject
    {
        void Initialize(string path);
        string GetFullPath();
        void Open(out bool isDir);
        void Copy(string dest);
        void Delete();
        void Move(string dest);
        void Rename(string newName);
        void isDir(out bool isDir);
    }


    interface ICatalog : IFSObject
    {
        void ReloadFiles();
        void GetFiles(out string[] files);
        void GetFileSystemEntries(out string[] entries);
        void GetDirectories(out string[] directories);
        CFSObject GetFile(int index);
        void CreateFile(string name);
        void CreateDirectory(string name);
    }


    abstract class CFSObject : IFSObject
    {
        public string caption;
        protected string fullPath;

        public void Initialize(string path)
        {
            caption = Path.GetFileName(path);
            fullPath = path;
        }

        public string GetFullPath()
        {
            return fullPath;
        }

        abstract public void Open(out bool isDir);
        abstract public void Copy(string dest);
        abstract public void Delete();
        abstract public void Move(string dest);
        abstract public void Rename(string newName);
        abstract public void isDir(out bool isDir);
    }


    class CFile : CFSObject
    {
        public CFile() : base() { }

        public override void Open(out bool isDir)
        {
            isDir = false;
            string commandText = fullPath;
            var proc = new System.Diagnostics.Process();
            proc.StartInfo.FileName = commandText;
            proc.StartInfo.UseShellExecute = true;
            proc.Start();
        }

        public override void Copy(string dest)
        {
            string source = fullPath;
            dest = Path.Combine(dest, caption);
            if (File.Exists(dest))
                dest = Path.Combine(Path.GetDirectoryName(dest), Path.GetFileNameWithoutExtension(dest) + " (Копия)" + Path.GetExtension(dest));
            File.Copy(source, dest, false);
        }

        public override void Delete()
        {
            File.Delete(fullPath);
        }

        public override void Move(string dest)
        {
            string newPath = Path.Combine(dest, caption);
            if (Path.GetPathRoot(fullPath) == Path.GetPathRoot(dest))
                File.Move(fullPath, newPath);
            else
            {
                File.Copy(fullPath, newPath);
                File.Delete(fullPath);
            }
            fullPath = newPath;
        }

        public override void Rename(string newName)
        {
            caption = newName;
            string newPath = Path.Combine(Directory.GetParent(fullPath).FullName, newName);
            File.Move(fullPath, newPath);
            fullPath = newPath;
        }

        public override void isDir(out bool isDir)
        {
            isDir = false;
        }
    }


    class CCatalog : CFSObject, ICatalog 
    {
        CFSObject[] files;

        public CCatalog()
            : base()
        {

        }

        public override void Copy(string dest)
        {
            // TODO
        }

        public override void Delete()
        {
            Directory.Delete(fullPath, true);
        }

        public override void Open(out bool isDir)
        {
            isDir = true;
        }

        public override void isDir(out bool isDir)
        {
            isDir = true;
        }

        public override void Rename(string newName)
        {
            string newPath = Path.Combine(Directory.GetParent(fullPath).FullName, newName);
            Directory.Move(fullPath, newPath);
            fullPath = newPath;
            caption = newName;
        }

        public override void Move(string dest)
        {
            string newPath = Path.Combine(dest, caption);
            Directory.Move(fullPath, newPath);
            fullPath = newPath;
        }

        public void ReloadFiles()
        {
            files = null;
            string[] fileNames;
            try
            {
                fileNames = Directory.GetFileSystemEntries(fullPath);
            }
            catch
            {
                return;
            }

            files = new CFSObject[fileNames.Length];
            for (int i = 0; i < fileNames.Length; i++)
            {
                if (File.Exists(fileNames[i]))
                {
                    files[i] = new CFile();
                    files[i].Initialize(fileNames[i]);
                }
                else
                {
                    files[i] = new CCatalog();
                    files[i].Initialize(fileNames[i]);
                }
            }
        }

        public void GetFiles(out string[] fileNames)
        {
            if (files == null)
            {
                fileNames = null;
                return;
            }
            int n = 0;
            foreach (var file in files)
                if (file is CFile)
                    n++;
            fileNames = new string[n];
            int i = 0;
            foreach(var file in files)
                if (file is CFile)
                    fileNames[i++] = file.caption;
        }

        public void GetFileSystemEntries(out string[] entries)
        {
            if (files == null)
            {
                entries = null;
                return;
            }
            int n = files.Length;
            entries = new string[n];
            for (int i = 0; i < n; i++)
                entries[i] = files[i].caption;
        }

        public void GetDirectories(out string[] directories)
        {
            if (files == null)
            {
                directories = null;
                return;
            }
            int n = 0;
            foreach (var file in files)
                if (file is CCatalog)
                    n++;
            directories = new string[n];
            int i = 0;
            foreach (var file in files)
                if (file is CCatalog)
                    directories[i++] = file.caption;
        }

        public CFSObject GetFile(int index)
        {
            return files[index];
        }

        public void CreateFile(string name)
        {
            string path = Path.Combine(fullPath, name);
            File.Create(path);
        }

        public void CreateDirectory(string name)
        {
            string path = Path.Combine(fullPath, name);
            Directory.CreateDirectory(path);
        }
    }
}
