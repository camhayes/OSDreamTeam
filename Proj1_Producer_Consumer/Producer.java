
public class Producer implements Runnable 
{
	private Buffer buffer;

    public Producer(Buffer buffer) 
    {
        this.buffer = buffer;
    }

    @Override
    public void run() 
    {
        try 
        {
            while (true) 
            {
                buffer.produce();
                buffer.displayState();
                // Simulate some work
                //Thread.sleep(1000); // regular sleep 1 sec
                //Thread.yield(); // will flip flop between being empty and full if both (producer & consumer) are on yield
                Thread.sleep(500 + (int) (Math.random() * 1000));
            }
        } 
        catch (InterruptedException e) 
        {
            e.printStackTrace();
        }
    }
}
