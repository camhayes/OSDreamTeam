public class Buffer 
{
	private static final int BUFFER_SIZE = 10; // Use this to change the buffer size, works best with 3-5
    private int[] buffer = new int[BUFFER_SIZE];
    private int count = 0;

    /**
     * Produces an element into the array and waits if it gets full
     * @throws InterruptedException
     */
    public synchronized void produce() throws InterruptedException 
    {
        while (count == BUFFER_SIZE) 
        {
            System.out.println("Buffer is full. Producer is waiting.");
            wait(); // waits till consumer has notifies that it emptied an element in the array
        }

        // Produce
        buffer[count] = 1; // Set to FULL
        count++;

        // Notify consumer that a new item is produced
        notifyAll();
    }

    /**
     * Consumes an element in the array and waits if it gets empty
     * @throws InterruptedException
     */
    public synchronized void consume() throws InterruptedException 
    {
        while (count == 0) 
        {
            System.out.println("Buffer is empty. Consumer is waiting.");
            wait(); // waits till producer has notifies that it filled an element in the array
        }

        // Consume
        count--;
        buffer[count] = 0; // Set to EMPTY

        // Notify producer that an item is consumed
        notifyAll();
    }

    /**
     * The array buffer being printed as an in between for visualization
     */
    public synchronized void displayState() 
    {
        System.out.print("Buffer state: ");
        for (int i = 0; i < BUFFER_SIZE; i++) 
        {
            System.out.print(buffer[i] + " ");
        }
        System.out.println();
    }
}
