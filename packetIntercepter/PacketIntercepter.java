//javac PacketIntercepter.java && sudo java PacketIntercepter
import java.io.IOException;

import javax.sound.midi.Receiver;

public class PacketIntercepter 
{
    public static void main(String[] args) throws IOException 
    {
        Server serv = new Server(5000);
        String rcvPkt;

        int ind = 0;

        while (true)
        {
            rcvPkt = serv.receive();

            //if (ind % 2 == 0)
            //{
                System.out.println("asdsda");
                serv.send(rcvPkt);
            //}

            ind++;
        }
        
    }

}