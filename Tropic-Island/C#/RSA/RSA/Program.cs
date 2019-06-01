using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace RSA
{
    class Program
    {
        static String codes2string(String str)
        {
            StringBuilder text = new StringBuilder();
            Byte[] bytes = new Byte[str.Length / 2];
            for(int i=0;i<str.Length/2;i++)
            {
                String code = str.Substring(2 * i, 2);
                bytes[i] = Byte.Parse(code);
            }
            return ASCIIEncoding.ASCII.GetString(bytes);
        }
        static void Main(string[] args)
        {
            BigInteger e = 12371;
            //BigInteger e = 12341;
            BigInteger n = 517815623413379;
            //BigInteger n = 565570077646207;
            //Факторизация n: в гугле Wolphram alpha factor(n)
            BigInteger p = 2432363;
            //BigInteger p = 1546379;
            BigInteger q = 212885833;
            //BigInteger q = 365738333;
            BigInteger phi = (p - 1) * (q - 1);
            Console.WriteLine("phi");
            Console.WriteLine("{0}", phi);
            
            //Обратный элемент d в кольце e,phi https://planetcalc.ru/3311/
            BigInteger d = 81621537934331;
            //BigInteger d = 143672396238821;
            Console.WriteLine("{0}", (d * e) % phi);//Здесь должна выводится единица

            String[] c_text = "127881381553746 56626484111508 435839351545312 207685619856968 320863251613810".Split(' ');
            //String[] c_text = "277140870674302 260217431481485 329310844916399 448964498705119".Split(' ');
            StringBuilder text = new StringBuilder();
            StringBuilder c_text_ = new StringBuilder();

            foreach(String c_str in c_text)
            {
                BigInteger c_msg = UInt64.Parse(c_str);
                BigInteger msg = BigInteger.ModPow(c_msg, d, n);
                text.Append(msg.ToString());

                BigInteger c_msg_ = BigInteger.ModPow(msg, e, n);
                c_text_.Append(c_msg_.ToString());
            }
            Console.WriteLine(c_text_);

            Console.WriteLine(codes2string(text.ToString()));
            
            Console.ReadKey();
        }
    }
}
