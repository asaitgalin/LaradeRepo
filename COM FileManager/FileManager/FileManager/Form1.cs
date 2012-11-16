using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using FileManagerServerLib;

namespace FileManager
{
    public partial class Form1 : Form
    {
        ICatalog Current;
        IntPtr node;
        string[] copied = null;
        bool cutted = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void файлToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool selected;
            if (listView1.SelectedItems.Count == 0)
                selected = false;
            else
                selected = true;
            открытьToolStripMenuItem.Enabled = selected;
            вставитьToolStripMenuItem.Enabled = selected;
            копироватьToolStripMenuItem.Enabled = selected;
            вырезатьToolStripMenuItem.Enabled = selected;
        }

        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            OpenFile();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            DriveInfo[] Drives = DriveInfo.GetDrives();
            string[] directories;
            ICatalog Current;
            TreeNode node;
            for (int i = 0; i < Drives.Length; i++)
            {
                treeView1.Nodes.Add(Drives[i].Name);
                if (Drives[i].DriveType == DriveType.Removable || Drives[i].DriveType == DriveType.CDRom)
                    continue;
                FolderObj fo = new FolderObj();
                Current = (ICatalog)fo;
                Current.Initialize(Drives[i].Name);
                Current.ReloadFiles();
                int n = Current.GetDirectoriesCount();
                if (n == 0)
                    continue;
                directories = new string[n];
                for (int j = 0; j < n; j++)
                    directories[j] = Current.GetDirectoryName(j);
                
                foreach (var directory in directories)
                {
                    node = new TreeNode(directory);
                    node.ImageIndex = 0;
                    treeView1.Nodes[i].Nodes.Add(node);
                }
            }
            for(int i=0; i < treeView1.Nodes.Count; i++)
            {
                DriveInfo di = new DriveInfo(treeView1.Nodes[i].Text);
                if (di.DriveType == DriveType.Fixed)
                {
                    treeView1.SelectedNode = treeView1.Nodes[i];
                    return;
                }
            }
        }

        private void OpenDir(string path)
        {
            ListViewItem lvi;
            FolderObj fo = new FolderObj();
            IFSObject temp = null;
            Current = (ICatalog)fo;
            Current.Initialize(path);
            Current.ReloadFiles();
            listView1.Items.Clear();
            string[] files;
            int n = Current.GetFileSystemEntriesCount();
            if (n == 0)
                return;
            files = new string[n];
            for (int i = 0; i < n; i++)
                files[i] = Current.GetFileSystemEntryName(i);
            for(int i=0; i < files.Length; i++)
            {
                temp = Current.GetFile(i);
                if (temp.isDir() == 1)
                    lvi = new ListViewItem(files[i], 0);
                else
                    lvi = new ListViewItem(files[i], 1);
                listView1.Items.Add(lvi);
            }
            textBox1.Text = path;
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Action != TreeViewAction.Expand && e.Action != TreeViewAction.Collapse)
                node = treeView1.SelectedNode.Handle;
            OpenDir(e.Node.FullPath);
            if (e.Node.Nodes.Count == 0)
                LoadDirs(e.Node);   
        }

        private void LoadDirs(TreeNode node)
        {
            FolderObj fo = new FolderObj();
            ICatalog temp = (ICatalog)fo;
            temp.Initialize(node.FullPath);
            temp.ReloadFiles();
            string[] directories;
            int n = temp.GetDirectoriesCount();
            if (n == 0)
                return;
            directories = new string[n];
            for (int i = 0; i < n; i++)
                directories[i] = temp.GetDirectoryName(i);
            foreach (var directory in directories)
                node.Nodes.Add(directory);
        }

        private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            ICatalog cat;
            TreeNode temp;
            foreach (TreeNode node in e.Node.Nodes)
            {
                node.Nodes.Clear();
                FolderObj fo = new FolderObj();
                cat = (ICatalog)fo;
                cat.Initialize(node.FullPath);
                string[] directories;
                cat.ReloadFiles();
                int n = cat.GetDirectoriesCount();
                if (n == 0)
                    continue;
                directories = new string[n];
                for (int i = 0; i < n; i++)
                    directories[i] = cat.GetDirectoryName(i);
                foreach (var dir in directories)
                {
                    temp = new TreeNode(dir);
                    temp.Name = dir;
                    node.Nodes.Add(temp);
                }
            }
        }

        private void открытьToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            OpenFile();
        }

        private void OpenFile()
        {
            if (listView1.SelectedItems.Count != 1)
                return;
            int item = listView1.SelectedItems[0].Index;
            IFSObject temp =  null;
            Current.ReloadFiles();
            temp = Current.GetFile(item);
            if (temp.Open() == 1)
            {
                string path = temp.GetFullPath();
                OpenDir(path);
                string name = Path.GetFileName(path);
                TreeNode nod = TreeNode.FromHandle(treeView1, node);
                treeView1.Focus();
                nod.Expand();
                foreach (TreeNode tempNode in nod.Nodes)
                    if (tempNode.Text == name)
                        treeView1.SelectedNode = tempNode;
            }
        }

        private void CreateFile()
        {
            ListViewItem lvi = new ListViewItem("", 1);
            lvi.Tag = "File";
            listView1.Items.Add(lvi);
            listView1.Items[listView1.Items.Count - 1].BeginEdit();
        }

        private void CreateDirectory()
        {
            ListViewItem lvi = new ListViewItem("Новая папка", 0);
            lvi.Tag = "Folder";
            listView1.Items.Add(lvi);
            listView1.Items[listView1.Items.Count - 1].BeginEdit();
        }

        private void Copy(bool cut)
        {
            int n = listView1.SelectedItems.Count;
            int item;
            copied = new string[n];
            for (int i = 0; i < n; i++)
            {
                item = listView1.SelectedItems[i].Index;
                IFSObject temp = Current.GetFile(item);
                copied[i] = temp.GetFullPath();
                Current.ReloadFiles();
            }
            cutted = cut;
        }

        private void Delete()
        {
            foreach (ListViewItem item in listView1.SelectedItems)
            {
                IFSObject temp = Current.GetFile(item.Index);
                temp.Delete();
            }
            OpenDir(Current.GetFullPath());
        }

        private void Paste()
        {
            IFSObject temp;
            foreach (var file in copied)
            {
                if (Directory.Exists(file))
                {
                    FolderObj fo = new FolderObj();
                    temp = (IFSObject)fo;
                }
                else
                {
                    FileObj fo = new FileObj();
                    temp = (IFSObject)fo;
                }
                temp.Initialize(file);
                if (cutted)
                    temp.Move(Current.GetFullPath());
                else
                    temp.Copy(Current.GetFullPath());
            }
            OpenDir(Current.GetFullPath());
            foreach(var file in copied)
                listView1.FindItemWithText(Path.GetFileName(file)).Selected = true;
        }

        private void FolderMenuStrip_Opening(object sender, CancelEventArgs e)
        {
            вставитьToolStripMenuItem3.Enabled = copied != null;
        }

        private void FileMenuStrip_Opening(object sender, CancelEventArgs e)
        {
            вставитьToolStripMenuItem1.Enabled = copied != null;
        }

        private void listView1_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                if (listView1.SelectedItems.Count == 0)
                    FolderMenuStrip.Show(listView1, e.Location);
                else
                    FileMenuStrip.Show(listView1, e.Location);
            }
        }

        private void копироватьToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Copy(false);
        }

        private void вырезатьToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            Copy(true);
        }

        private void вставитьToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Paste();
        }

        private void удалитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Delete();
        }

        private void listView1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control)
                switch (e.KeyCode)
                {
                    case Keys.X:
                        Copy(true);
                        break;
                    case Keys.C:
                        Copy(false);
                        break;
                    case Keys.V:
                        Paste();
                        break;
                }
            if (e.KeyCode == Keys.Delete)
                Delete();
        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void копироватьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Copy(false);
        }

        private void вырезатьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Copy(true);
        }

        private void файлToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            CreateFile();
        }

        private void создатьФайлToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CreateFile();
        }

        private void listView1_AfterLabelEdit(object sender, LabelEditEventArgs e)
        {
            int num = e.Item;
            string text = listView1.Items[num].Text;
            IFSObject temp;
            if (listView1.Items[num].Tag == null)
            {
                temp = Current.GetFile(num);
                temp.Rename(text);
            }
            else if (listView1.Items[num].Tag.ToString() == "File")
                Current.CreateFile(text);
            else if (listView1.Items[num].Tag.ToString() == "Folder")
                Current.CreateDirectory(text);
            OpenDir(Current.GetFullPath());
            try
            {
                listView1.FindItemWithText(text).Selected = true;
            }
            catch { }
        }

        private void создатьПапкуToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CreateDirectory();
        }

        private void папкуToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CreateDirectory();
        }

        private void переименоватьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count != 1)
                return;
            listView1.SelectedItems[0].BeginEdit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
                OpenDir(textBox1.Text);
        }
    }
}


namespace FileManagerServerLib
{
    [ComImport, Guid("01018ECD-F895-4939-B909-AB2E117814F2")]
    class FileObj { }
    [ComImport, Guid("87F86C92-0F52-4468-BBD4-B6742F2AF96C")]
    class FolderObj { }
}