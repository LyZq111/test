		#include<iostream>
		using namespace std;

		// 定义包头结构体
		struct dataHeader 
		{
			int8_t Preprocessing;// 预处理状态字段
			int8_t TargetDetection;// 目标检测状态字段
			int8_t TargetTracking;// 目标跟踪状态字段
			int8_t TrackUpdateMaintenance;// 航迹更新和维护状态字段
			int8_t TrackAnalysis;// 航迹分析状态字段
		};

		//目标类型
		struct targetType
		{
			string     TargetID;          // 目标识别号
			double   Range;             // 目标距离（单位：米）
			double   Azimuth;           // 目标方位角（单位：弧度）
			double   Elevation;         // 目标俯仰角（单位：弧度）
			double   RadialSpeed;       // 目标径向速度（单位：米/秒）
			double   RCS;               // 目标雷达截面积（RCS）
			double   Altitude;          // 目标高度（例如，如果是飞行器）（单位：米）
			double   CourseAngle;       // 目标航向角（例如，如果是飞行器）（单位：弧度）
			double   PitchAngle;        // 目标俯仰角（例如，如果是飞行器）（单位：弧度）
			double   TargetSize;        // 目标大小
		};
		//天线朝向信息
		struct antenna
		{
			//方位角
			//俯仰角
			//方位扫描范围
			//俯仰扫描范围


		};

		//波形参数
		struct boxin
		{
			double Freqency;//频点
			//重频，单位时间内的重复次数
			//脉宽
			//距离门
			//带宽


		};

		//控制参数--没有协议
		struct control
		{
			uint16_t Working_mode;//工作模式
			uint16_t Servo_control;//伺服控制
			uint16_t Frequency;//频点控制
			//接收衰减控制
			//威力范围控制
			boxin Boxin;//波形参数
		};

		// 定义点迹的结构体
		struct RadarTrack
		{
			int32_t Timestamp; // 时间戳
			double X; // x坐标
			double Y; // y坐标
			double Velocity; // 速度
			double Intensity; // 强度
			double Rcs; // 雷达截面积
		
		};
		//雷达状态信息--上位机
		struct status
		{
			bool Power;  //电源开关
			double Voltage; //电压？？
			double Current; //电流？？
			double Antenna; //天线朝向
			double Temperature;//温度？？
			//CPU占用
			//GPU占用
			//磁盘占用
			//频点
			//传输带宽
			control	Control;//控制参数

		};
		//系统状态信息
		struct Systemstatus 
		{
			double SysVoltage;//系统电压
			double SysCurrent;//系统电流
			double TRtemperature;//TR组件温度
			double CPUsage;//CPU使用率
			double GPUsage;//GPU使用率
			//内存使用率
			//目标检测准确性
			//目标检测误报率
			//目标检测置信度
			//跟踪性能准确率
			//跟踪性能误报率
			//跟踪性能置信度
			//系统健康状态
			//任务队列及错误信息
		};
		//雷达标校gps
		struct GPSData
		{
			uint32_t timestamp;   // 时间戳，格式：hhmmss.ss
			double latitude;    // 纬度,N/S
			double longitude;   // 经度,N/S
			double altitude;    // 海拔高度
			//HDOP水平精度因子
			//正在使用的卫星数量
			//校验值
			//差分时间（从最近一次接收到差分信号开始的秒数,如果不是差分定位将为空）
			//差分站ID号0000 - 1023(前导位数不足则补0,如果不是差分定位将为空)
			//GPS状态（0=未定位,1=非差分定位,2=差分定位,3=无效PPS,6=正在估算）
		};

		//数据处理模块发送至雷达的参数
		struct send_radar
		{

			uint32_t            head=0x11111111111111;   //包头
			//dataHeader          Header;                 //信号处理的包头？？？？？
			uint32_t            Timestamps;              //时间
			uint16_t            Center_frequency_GHz;    //频率
			uint16_t            Bandwidth_MHz;           //带宽(MHz)
			uint16_t            FM_Slope_MHz_us_Mul_10; // 调频斜率
			uint16_t            AD_Sample_Rate_KHz;      //采样率
			uint16_t            Samples_No;             //采样点个数
			uint32_t            AD_Sample_start_time_us; //采样起始时间   
			uint16_t            Number_pulses;           //脉冲雷达个数
			uint16_t            Pulse_radar_cycle;        //脉冲雷达周期
			uint16_t            Operating_mode;          //工作模式
			control        Control;                 //控制参数
		};

		//数据处理模块接受信号处理的参数
		struct Received_radar
		{
			uint32_t            head = 0x11111111111111;   //包头
		   // dataHeader           Header;          // 数据处理的包头
			uint32_t            Timestamps;              //时间
			uint16_t            Center_frequency_GHz;    //频率
			uint16_t            Bandwidth_MHz;           //带宽(MHz)
			uint16_t            FM_Slope_MHz_us_Mul_10; // 调频斜率
			uint16_t            AD_Sample_Rate_KHz;      //采样率
			uint16_t            Samples_No;             //采样点个数
			uint32_t            AD_Sample_start_time_us; //采样起始时间   
			uint16_t            Number_pulses;           //脉冲雷达个数
			uint16_t            Pulse_radar_cycle;        //脉冲雷达周期
			uint16_t            Operating_mode;          //工作模式
			RadarTrack radarTrack[100]; // 声明一个包含100个RadarTrack结构体的数组(具体数值待确定)
		};


		//数据处理模块发送至雷视融合
		struct radar_vision_fusion
		{
			uint32_t head = 0x11111111111111;   //包头
			uint32_t TrackID;     // 航迹ID
			double Timestamp;     // 时间戳（单位：秒）
			double Latitude;      // 纬度
			double Longitude;     // 经度
			double Altitude;      // 高度
			double Speed;         // 速度
			double Heading;       // 航向角
			int32_t Gps;              //gps信息
			targetType TargetType; // 目标类型
			double Confidence; // 航迹置信度
		};
		//数据处理模块发送至上位机
		struct host_computer
		{
			uint32_t  head = 0x11111111111111;   //包头
			int TrackID;          // 航迹ID
			double Timestamp;     // 时间戳（单位：秒）
			double Latitude;      // 纬度
			double Longitude;     // 经度
			double Altitude;      // 高度
			double Speed;         // 速度
			double Heading;       // 航向角
			GPSData Gps;              //gps信息
			targetType TargetType;// 目标类型
			double confidence; // 航迹置信度
			status Status;       //雷达状态
			status SystemStatus;//系统状态

		};
