		#include<iostream>
		using namespace std;

		// �����ͷ�ṹ��
		struct dataHeader 
		{
			int8_t Preprocessing;// Ԥ����״̬�ֶ�
			int8_t TargetDetection;// Ŀ����״̬�ֶ�
			int8_t TargetTracking;// Ŀ�����״̬�ֶ�
			int8_t TrackUpdateMaintenance;// �������º�ά��״̬�ֶ�
			int8_t TrackAnalysis;// ��������״̬�ֶ�
		};

		//Ŀ������
		struct targetType
		{
			string     TargetID;          // Ŀ��ʶ���
			double   Range;             // Ŀ����루��λ���ף�
			double   Azimuth;           // Ŀ�귽λ�ǣ���λ�����ȣ�
			double   Elevation;         // Ŀ�긩���ǣ���λ�����ȣ�
			double   RadialSpeed;       // Ŀ�꾶���ٶȣ���λ����/�룩
			double   RCS;               // Ŀ���״�������RCS��
			double   Altitude;          // Ŀ��߶ȣ����磬����Ƿ�����������λ���ף�
			double   CourseAngle;       // Ŀ�꺽��ǣ����磬����Ƿ�����������λ�����ȣ�
			double   PitchAngle;        // Ŀ�긩���ǣ����磬����Ƿ�����������λ�����ȣ�
			double   TargetSize;        // Ŀ���С
		};
		//���߳�����Ϣ
		struct antenna
		{
			//��λ��
			//������
			//��λɨ�跶Χ
			//����ɨ�跶Χ


		};

		//���β���
		struct boxin
		{
			double Freqency;//Ƶ��
			//��Ƶ����λʱ���ڵ��ظ�����
			//����
			//������
			//����


		};

		//���Ʋ���--û��Э��
		struct control
		{
			uint16_t Working_mode;//����ģʽ
			uint16_t Servo_control;//�ŷ�����
			uint16_t Frequency;//Ƶ�����
			//����˥������
			//������Χ����
			boxin Boxin;//���β���
		};

		// ����㼣�Ľṹ��
		struct RadarTrack
		{
			int32_t Timestamp; // ʱ���
			double X; // x����
			double Y; // y����
			double Velocity; // �ٶ�
			double Intensity; // ǿ��
			double Rcs; // �״�����
		
		};
		//�״�״̬��Ϣ--��λ��
		struct status
		{
			bool Power;  //��Դ����
			double Voltage; //��ѹ����
			double Current; //��������
			double Antenna; //���߳���
			double Temperature;//�¶ȣ���
			//CPUռ��
			//GPUռ��
			//����ռ��
			//Ƶ��
			//�������
			control	Control;//���Ʋ���

		};
		//ϵͳ״̬��Ϣ
		struct Systemstatus 
		{
			double SysVoltage;//ϵͳ��ѹ
			double SysCurrent;//ϵͳ����
			double TRtemperature;//TR����¶�
			double CPUsage;//CPUʹ����
			double GPUsage;//GPUʹ����
			//�ڴ�ʹ����
			//Ŀ����׼ȷ��
			//Ŀ��������
			//Ŀ�������Ŷ�
			//��������׼ȷ��
			//������������
			//�����������Ŷ�
			//ϵͳ����״̬
			//������м�������Ϣ
		};
		//�״��Уgps
		struct GPSData
		{
			uint32_t timestamp;   // ʱ�������ʽ��hhmmss.ss
			double latitude;    // γ��,N/S
			double longitude;   // ����,N/S
			double altitude;    // ���θ߶�
			//HDOPˮƽ��������
			//����ʹ�õ���������
			//У��ֵ
			//���ʱ�䣨�����һ�ν��յ�����źſ�ʼ������,������ǲ�ֶ�λ��Ϊ�գ�
			//���վID��0000 - 1023(ǰ��λ��������0,������ǲ�ֶ�λ��Ϊ��)
			//GPS״̬��0=δ��λ,1=�ǲ�ֶ�λ,2=��ֶ�λ,3=��ЧPPS,6=���ڹ��㣩
		};

		//���ݴ���ģ�鷢�����״�Ĳ���
		struct send_radar
		{

			uint32_t            head=0x11111111111111;   //��ͷ
			//dataHeader          Header;                 //�źŴ���İ�ͷ����������
			uint32_t            Timestamps;              //ʱ��
			uint16_t            Center_frequency_GHz;    //Ƶ��
			uint16_t            Bandwidth_MHz;           //����(MHz)
			uint16_t            FM_Slope_MHz_us_Mul_10; // ��Ƶб��
			uint16_t            AD_Sample_Rate_KHz;      //������
			uint16_t            Samples_No;             //���������
			uint32_t            AD_Sample_start_time_us; //������ʼʱ��   
			uint16_t            Number_pulses;           //�����״����
			uint16_t            Pulse_radar_cycle;        //�����״�����
			uint16_t            Operating_mode;          //����ģʽ
			control        Control;                 //���Ʋ���
		};

		//���ݴ���ģ������źŴ���Ĳ���
		struct Received_radar
		{
			uint32_t            head = 0x11111111111111;   //��ͷ
		   // dataHeader           Header;          // ���ݴ���İ�ͷ
			uint32_t            Timestamps;              //ʱ��
			uint16_t            Center_frequency_GHz;    //Ƶ��
			uint16_t            Bandwidth_MHz;           //����(MHz)
			uint16_t            FM_Slope_MHz_us_Mul_10; // ��Ƶб��
			uint16_t            AD_Sample_Rate_KHz;      //������
			uint16_t            Samples_No;             //���������
			uint32_t            AD_Sample_start_time_us; //������ʼʱ��   
			uint16_t            Number_pulses;           //�����״����
			uint16_t            Pulse_radar_cycle;        //�����״�����
			uint16_t            Operating_mode;          //����ģʽ
			RadarTrack radarTrack[100]; // ����һ������100��RadarTrack�ṹ�������(������ֵ��ȷ��)
		};


		//���ݴ���ģ�鷢���������ں�
		struct radar_vision_fusion
		{
			uint32_t head = 0x11111111111111;   //��ͷ
			uint32_t TrackID;     // ����ID
			double Timestamp;     // ʱ�������λ���룩
			double Latitude;      // γ��
			double Longitude;     // ����
			double Altitude;      // �߶�
			double Speed;         // �ٶ�
			double Heading;       // �����
			int32_t Gps;              //gps��Ϣ
			targetType TargetType; // Ŀ������
			double Confidence; // �������Ŷ�
		};
		//���ݴ���ģ�鷢������λ��
		struct host_computer
		{
			uint32_t  head = 0x11111111111111;   //��ͷ
			int TrackID;          // ����ID
			double Timestamp;     // ʱ�������λ���룩
			double Latitude;      // γ��
			double Longitude;     // ����
			double Altitude;      // �߶�
			double Speed;         // �ٶ�
			double Heading;       // �����
			GPSData Gps;              //gps��Ϣ
			targetType TargetType;// Ŀ������
			double confidence; // �������Ŷ�
			status Status;       //�״�״̬
			status SystemStatus;//ϵͳ״̬

		};
