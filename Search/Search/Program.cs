using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace Search
{
    class Program
    {
        static void Main(string[] args)
        {
            Crawler crawler = new Crawler( new FileProcessor(), @"C:\temp" );
            crawler.DoWork();
            return;
            string file1 = @"C:\temp\08.11.2011\08.11.2011\WindowsFormsApplication10\WindowsFormsApplication10\EnteringAssesments.resx";
            string file2 = @"C:\temp\08.11.2011\08.11.2011\WindowsFormsApplication10\WindowsFormsApplication10\Form4.resx";
            FileStream fs = new FileStream(file1, FileMode.Open, FileAccess.Read);
            byte[] buff = new byte[fs.Length];
            fs.Read(buff, 0, buff.Length);
            SHA256 mys = SHA256.Create();
            long hash1 = BitConverter.ToInt64(mys.ComputeHash(buff), 0);
            fs.Close();
            fs = new FileStream(file2, FileMode.Open, FileAccess.Read);
            buff = new byte[fs.Length];
            fs.Read(buff, 0, buff.Length);
            long hash2 = BitConverter.ToInt64(mys.ComputeHash(buff), 0);
            fs.Close();
            Console.WriteLine(hash1);
            Console.WriteLine(hash2);
        }
    }
}
