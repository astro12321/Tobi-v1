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

    private String helloMsg = "HELLO astro !";
    private String helloBackMsg = "HI astro !";
    private static int BUFFERSIZE = 2000;


    public Server(int port) throws IOException
    {
        socket = new DatagramSocket(port);

        String helloMsg = receive();

        if (this.helloMsg.equals(helloMsg))
        {
            System.out.println("Client connected !");
            send(helloBackMsg);
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