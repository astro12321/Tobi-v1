

public class thr implements Runnable 
{
    Server serv;

    public thr(Server serv) 
    {
        this.serv = serv;
    }

 
    public void run() 
    {
        System.out.println("In thread");

        try
        {
            while (true)
            {
                PacketManager.packetQueue.add(serv.receive());
                //System.out.println("Packet added to queue: " + PacketManager.packetQueue.peek());
            }
        }
        catch (Exception e)
        {
            System.out.println("Oupsss " + e.toString());
        }

    }

 }