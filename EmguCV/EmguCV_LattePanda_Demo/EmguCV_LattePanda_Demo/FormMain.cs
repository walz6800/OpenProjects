using System;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.Aruco;

namespace EmguCV_LattePanda_Demo
{
    public partial class MainForm : Form
    {
        private VideoCapture _capture_CAM1;
        private VideoCapture _capture_CAM2;

        private DetectorParameters _detectorParameters_CAM1;
        private DetectorParameters _detectorParameters_CAM2;

        public MainForm()
        {
            InitializeComponent();

            _detectorParameters_CAM1 = DetectorParameters.GetDefault();
            _detectorParameters_CAM2 = DetectorParameters.GetDefault();

            try
            {
                _capture_CAM1 = new VideoCapture(0);
                if (!_capture_CAM1.IsOpened)
                {
                    _capture_CAM1 = null;
                    throw new NullReferenceException("Unable to open CAM1 video capture");
                }
                else
                {
                    _capture_CAM1.ImageGrabbed += ProcessFrame_CAM1;
                }
            }
            catch (NullReferenceException excpt)
            {
                MessageBox.Show(excpt.Message);
            }

            try
            {
                _capture_CAM2 = new VideoCapture(1);
                if (!_capture_CAM2.IsOpened)
                {
                    _capture_CAM2 = null;
                    throw new NullReferenceException("Unable to open CAM2 video capture");
                }
                else
                {
                    _capture_CAM2.ImageGrabbed += ProcessFrame_CAM2;
                }
            }
            catch (NullReferenceException excpt)
            {
                MessageBox.Show(excpt.Message);
            }

            UpdateMessage_CAM1(String.Empty);
            UpdateMessage_CAM2(String.Empty);
        }

        private void UpdateMessage_CAM1(string message)
        {
            if (this.InvokeRequired)
            {
                this.Invoke((Action)delegate { UpdateMessage_CAM1(message); });
                return;
            }

            MsgLabel1.Text = message;
        }

        private void UpdateMessage_CAM2(string message)
        {
            if (this.InvokeRequired)
            {
                this.Invoke((Action)delegate { UpdateMessage_CAM2(message); });
                return;
            }

            MsgLabel2.Text = message;
        }

        Mat _frame_CAM1 = new Mat();
        Mat _frameCopy_CAM1 = new Mat();
        Mat _frame_CAM2 = new Mat();
        Mat _frameCopy_CAM2 = new Mat();

        private void ProcessFrame_CAM1(object sender, EventArgs arg)
        {
            if (_capture_CAM1 != null && _capture_CAM1.Ptr != IntPtr.Zero)
            {
                _capture_CAM1.Retrieve(_frame_CAM1, 0);
                _frame_CAM1.CopyTo(_frameCopy_CAM1);
                CAM1_ImageBox.Image = _frameCopy_CAM1.Clone();
                //UpdateMessage("Open VideoCapture");
            }
            else
            {
                UpdateMessage_CAM1("VideoCapture was not created");
            }
        }

        private void ProcessFrame_CAM2(object sender, EventArgs arg)
        {
            if (_capture_CAM2 != null && _capture_CAM2.Ptr != IntPtr.Zero)
            {
                _capture_CAM2.Retrieve(_frame_CAM2, 0);
                _frame_CAM2.CopyTo(_frameCopy_CAM2);
                CAM2_ImageBox.Image = _frameCopy_CAM2.Clone();
                //UpdateMessage("Open VideoCapture");
            }
            else
            {
                UpdateMessage_CAM2("VideoCapture was not created");
            }
        }

        private void StartCAM1_Click(object sender, EventArgs e)
        {
            if (_capture_CAM1 != null)
            {
                _capture_CAM1.Start();
            }
        }

        private void StopCAM1_Click(object sender, EventArgs e)
        {
            if (_capture_CAM1 != null)
            {
                _capture_CAM1.Pause();
            }
        }

        private void StartCAM2_Click(object sender, EventArgs e)
        {
            if (_capture_CAM2 != null)
            {
                _capture_CAM2.Start();
            }
        }

        private void StopCAM2_Click(object sender, EventArgs e)
        {
            if (_capture_CAM2 != null)
            {
                _capture_CAM2.Pause();
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_capture_CAM1 != null)
            {
                _capture_CAM1.Stop();
            }
            if (_capture_CAM2 != null)
            {
                _capture_CAM2.Stop();
            }
            
        }

    }
}
