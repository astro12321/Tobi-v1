//javac PacketIntercepter.java && sudo java PacketIntercepter
import java.io.IOException;
import javax.sound.midi.Receiver;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.TimeUnit;


public class PacketIntercepter
{
    public static void main(String[] args) throws IOException, InterruptedException
    {
        Server serv = new Server(5000);
        String rcvPkt;
        int ind = 0;


        /*Runnable r = new thr(serv);
        new Thread(r).start();*/

        while (true)
        {
            //TimeUnit.MILLISECONDS.sleep(100); //Works when we wait

            ind++;

            rcvPkt = serv.receive();
            serv.send(rcvPkt);

            /*if (PacketManager.packetQueue.size() > 0)
            {
                if (ind % 5 == 0)
                {
                    serv.send(PacketManager.packetQueue.peek());

                    System.out.println("Sending...");

                    PacketManager.packetQueue.remove();
                }
                else{
                    System.out.println("We drop this one: " + PacketManager.packetQueue.peek());

                    PacketManager.packetQueue.remove();
                }

            }*/

        }
        
    }

}