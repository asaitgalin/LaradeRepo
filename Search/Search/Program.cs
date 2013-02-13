using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using System.Data.SqlClient;

namespace Search
{
    class Program
    {
        static void Main(string[] args)
        {
            Crawler crawler = new Crawler( new FileProcessor(), @"C:\temp" );
            crawler.DoWork();
        }
    }
}
