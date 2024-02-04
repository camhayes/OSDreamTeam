
public class Consumer implements Runnable 
{
	private Buffer buffer;

    public Consumer(Buffer buffer) 
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
                buffer.consume();
                buffer.displayState();
                // Simulate some work
                //Thread.sleep(1500); // regular sleep 1.5 secs
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
