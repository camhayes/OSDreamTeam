
public class Threads {

	public static void main(String[] args) 
	{
		Buffer buffer = new Buffer();

        // Create producer and consumer threads
        Thread producerThread = new Thread(new Producer(buffer));
        Thread consumerThread = new Thread(new Consumer(buffer));

        // Start the threads
        producerThread.start();
        consumerThread.start();
	}

}
