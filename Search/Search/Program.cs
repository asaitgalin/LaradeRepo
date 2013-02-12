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
            //SqlConnection connection;
            //SqlCommand command;
            //SqlDataReader dataReader;
            //string connectionString = "Server = 93.175.2.42\\SQLEXPRESS; Database = MIPTSearch; User Id=DuXeN0N; Password=2191019;";
            //connection = new SqlConnection(connectionString);
            //connection.Open();
            //command = new SqlCommand("SELECT * FROM Extensions", connection);
            //dataReader = command.ExecuteReader();
            //dataReader.Read();
            //Console.WriteLine(dataReader[1]);
            //dataReader.Close();
            TagsReader tr = new TagsReader();
            tr.LoadTags(@"d:\Music\100_rock_best\012. AC-DC - T.N.T..mp3");
            Console.WriteLine(tr.Title);
            Console.WriteLine(tr.Artist);
            Console.WriteLine(tr.Album);
            Console.WriteLine(tr.Year);
        }
    }
}
