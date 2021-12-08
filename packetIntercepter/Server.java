import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Arrays;


public class Server
{
    private DatagramSocket socket;
    private DatagramPacket client;

    private String syn = "SYN";
    private String synack = "SYNACK";
    private String ack = "ACK";
    private static int BUFFERSIZE = 4096;


    public Server(int port) throws IOException
    {
        socket = new DatagramSocket(port);

        String synReceived = receive();

        if (this.syn.equals(synReceived))
        {
            send(synack);

            System.out.println("ici");

            String ackReceived = receive();    

            System.out.println("la");

            if (this.ack.equals(ackReceived))
            {
                System.out.println("Client connected !");
            }
        }
        else
            System.out.println("Wrong hello message :(");
    }


    public String receive() throws IOException
    {
        byte[] msgBytes = new byte[BUFFERSIZE];
        DatagramPacket client;

        client = new DatagramPacket(msgBytes, msgBytes.length);

        if (this.client == null) //S'assure d'avoir le meme client lorsqu'on reply
            this.client = client;

        socket.receive(client);

        return BytesToString(msgBytes); 
    }


    public void send(String msg) throws IOException
    {
        InetAddress IP = client.getAddress();
        int port = client.getPort();

        byte[] msgBytes = msg.getBytes();

        socket.send(new DatagramPacket(msgBytes, msgBytes.length, IP, port));
    }


    public static String BytesToString(byte[] bytes)
    {
        String s = new String();
        int i = 0;

        while (bytes[i] != 0)
        {
            s += (char)bytes[i];
            i++;
        }

        return s;
    }

}