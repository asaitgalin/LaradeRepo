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
            //Crawler crawler = new Crawler( new FileProcessor(), @"\\natalie.campus\incoming\! Botanstvo\" );
            //crawler.DoWork();
            //return;
            SqlCommand cmd = new SqlCommand("SELECT * FROM TABLE WHERE a = @a");
            cmd.Parameters.Add("@a", System.Data.SqlDbType.NVarChar);
            cmd.Parameters["@a"].Value = "._Icon";
            Console.WriteLine(cmd.Parameters["@a"].Value);
        }
    }
}
