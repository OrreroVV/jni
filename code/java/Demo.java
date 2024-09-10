import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Demo {
    public native String sayHello(int a);

    static {
        System.loadLibrary("hzh"); 
    }

    public static void main(String[] args) {
        Demo demo = new Demo();

        ExecutorService executor = Executors.newSingleThreadExecutor();

        Future<String> futureResult = executor.submit(new Callable<String>() {
            @Override
            public String call() throws Exception {
                return demo.sayHello(3);  // 调用 native 方法
            }
        });

        System.out.println("Main thread continues running...");

        try {
            String result = futureResult.get(); 
            System.out.println("Result from sayHello: " + result);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        executor.shutdown();
    }
}
