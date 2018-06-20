using System;
using System.Threading;
using System.Xml.Schema;


namespace Threads
{
    class Program
    {
        static void Main(string[] args)
        {
            
            int num_thr = Convert.ToInt32(args[0]); 
            long count = 0;
            var st = DateTime.Now;
            Calc[] calcs = new Calc[num_thr];
            Thread[] threads = new Thread[num_thr];
            int size =  Convert.ToInt32(args[1]); 
            for (int i = 0; i < num_thr; i++)
            {
                calcs[i] = new Calc(num_thr,i,size);
                threads[i] = new Thread(calcs[i].run);
                threads[i].Start();
            }

            for (int i = 0; i < num_thr; i++)
            {
                threads[i].Join();
                count += calcs[i].count;
            }

            var end = DateTime.Now;
            Console.WriteLine("Count = " + count+" Time = "+(end-st));
            
        }
    }

    class Calc
    {
        private int size = 0;//10000000;//100000001
        public int thr_num;
        public int thr_id;
        public long count = 0;

        public Calc(int thrNum, int thrId, int size1)
        {
            thr_num = thrNum;
            thr_id = thrId;
            size = size1;
        }
        public void run(){
            long star=size/thr_num*thr_id;
            long end;
            if(thr_id==thr_num-1)
                end=size;
            else
                end=size/thr_num*(thr_id+1);
            if (star%2==0)
                star++;
            for (var i = star; i < end; i+=2) {
                var is_simple = true;
                for (long j = 3; j < Math.Sqrt(i)+1; j+=2) {
                    if(i%j==0) {
                        is_simple = false;
                        break;
                    }
                }
                if(is_simple)
                    count++;
            }
        }
    }
}