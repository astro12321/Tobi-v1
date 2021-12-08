//javac PacketIntercepter.java && sudo java PacketIntercepter
import java.io.IOException;

public class PacketIntercepter 
{
    public static void main(String[] args) throws IOException 
    {
        Server serv = new Server(5000);

        while (true)
        {
            String rawPkt = serv.receive();
            System.out.println(rawPkt);

            //return;
        }

    }

}