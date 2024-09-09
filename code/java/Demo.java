import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Demo {
    // 声明 native 方法
    public native String sayHello(int a);

    // 加载本地库
    static {
        System.loadLibrary("hzh");  // 加载本地库 hzh
    }

    public static void main(String[] args) {
        // 创建一个 Demo 类的对象
        Demo demo = new Demo();

        // 创建线程池
        ExecutorService executor = Executors.newSingleThreadExecutor();

        // 提交一个异步任务，返回值是 String 类型
        Future<String> futureResult = executor.submit(new Callable<String>() {
            @Override
            public String call() throws Exception {
                return demo.sayHello(100);  // 调用 native 方法
            }
        });

        // 主线程继续执行其他任务
        System.out.println("Main thread continues running...");

        // 获取异步任务的结果
        try {
            String result = futureResult.get();  // 阻塞直到获取到返回值
            System.out.println("Result from sayHello: " + result);
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        // 关闭线程池
        executor.shutdown();
    }
}
