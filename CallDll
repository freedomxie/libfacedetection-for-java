import com.sun.jna.win32.StdCallLibrary;
import java.awt.image.BufferedImage;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;
import static org.opencv.imgproc.Imgproc.resize;

/**
 *
 * @author freedom.xie
 */
public class CallDll {

    static {
        System.load("C:\\app\\opencv3.4\\build\\java\\x64\\opencv_java340.dll");
        System.load("C:\\app\\libfacedetection\\bin\\libfacedetect-x64.dll");
    }

   
    private JFrame frame = null;
    private JLabel label = null;

    public interface CLibrary extends StdCallLibrary {
        //定义并初始化接口的静态变量

       CLibrary Instance = (CLibrary) Native.loadLibrary("FaceDete.dll", CLibrary.class);
       String MutFaceDetectRF(byte[] img, int cols, int rows, int step);
       String MutFaceDetect(byte[] img, int cols, int rows, int step);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        
        Mat mat = Imgcodecs.imread("C:\\Users\\Administrator\\Desktop\\test\\test\\yes\\099_cp.jpg");
      
        if (mat.cols() > 600) {
            float temp = (float) mat.rows() / mat.cols();
            resize(mat, mat, new Size(600, Math.round(600 * temp)));
        }
        Mat gray = new Mat();
        Imgproc.cvtColor(mat, gray, Imgproc.COLOR_BGR2GRAY);
              
        int cols = gray.cols();
        int rows = gray.rows();
        int elemSize = (int) gray.elemSize();
        byte[] data = new byte[cols * rows * elemSize];
        gray.get(0, 0, data);
        String result = CLibrary.Instance.MutFaceDetect(data,cols,rows,(int)gray.step1());
        System.out.println(result);
        String rect[] = result.split(",");
        
        int x = Integer.parseInt(rect[0]);
        int y = Integer.parseInt(rect[1]);
        int w = Integer.parseInt(rect[2]);
        int h = Integer.parseInt(rect[2]);
        
        Imgproc.rectangle(mat, new Point(x,y), new Point(x+w,y+h),new Scalar(0, 255, 0), 1, 8, 0);
        new CallDll().imshow("aa", mat);
    }

    private void imshow(String name, Mat mat) {
        frame = new JFrame(name);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);
        label = new JLabel("");
        frame.getContentPane().add(label);
        frame.setVisible(true);
        frame.setBounds(100, 100, mat.cols() + 100, mat.rows() + 100);
        label.setBounds(0, 0, mat.cols() + 30, mat.rows() + 30);
        label.setIcon(new ImageIcon(this.matToBufferImg(mat)));
    }

    private BufferedImage matToBufferImg(Mat matrix) {
        int cols = matrix.cols();
        int rows = matrix.rows();
        int elemSize = (int) matrix.elemSize();
        byte[] data = new byte[cols * rows * elemSize];
        int type;
        matrix.get(0, 0, data);
        switch (matrix.channels()) {
            case 1:
                type = BufferedImage.TYPE_BYTE_GRAY;
                break;
            case 3:
                type = BufferedImage.TYPE_3BYTE_BGR;
                // bgr to rgb
                byte b;
                for (int i = 0; i < data.length; i = i + 3) {
                    b = data[i];
                    data[i] = data[i + 2];
                    data[i + 2] = b;
                }
                break;
            default:
                return null;
        }
        BufferedImage image = new BufferedImage(cols, rows, type);
        image.getRaster().setDataElements(0, 0, cols, rows, data);
        return image;
    }
}
