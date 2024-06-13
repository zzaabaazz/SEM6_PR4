#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <random>

#define N 5 // Длительность входной реализации смеси сигнала с шумом в шагах дискретизации


namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Button^ button1;






	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(29, 34);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Legend = L"Legend1";
			series2->Name = L"Series2";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(575, 287);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &MyForm::chart1_Click);
			//chart1->Series[0]->Name = "m_rek";
			//chart1->Series[1]->Name = "m_ist";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(58, 7);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(634, 349);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->chart1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void chart1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//2.	В результате эксперимента получена следующая реализация: 2, 1, 0, -2, 5. Построить рекуррентную оценку дисперсии.


		array<double>^ ee = gcnew array<double>(5);
		array<double>^ m_rek = gcnew array<double>(5);
		array<double>^ m_ist = gcnew array<double>(5);


		int a0;
		int i;





		ee[0] = 2;
		ee[1] = 1;
		ee[2] = 0;
		ee[3] = -2;
		ee[4] = 5;

		m_rek[1] = ee[1];

		for (i = 2; i < N; i++)
		{
			m_rek[i] = (i - 1.0) / i * m_rek[i - 1] + 1.0 / i * ee[i];
		}

		for (int n = 0; n < N; n++) {
			
			chart1->Series[0]->Points->AddXY(n, m_rek[n]);
			chart1->Series[1]->Points->AddXY(n, m_ist[n]);


		}
	}
		   double gauss(double mean, double stddev)
		   {//Box muller method
			   static double n2 = 0.0;
			   static int n2_cached = 0;
			   if (!n2_cached)
			   {
				   double x, y, r;
				   do
				   {
					   x = 2.0 * rand() / RAND_MAX - 1;
					   y = 2.0 * rand() / RAND_MAX - 1;

					   r = x * x + y * y;
				   } while (r == 0.0 || r > 1.0);
				   {
					   double d = sqrt(-2.0 * log(r) / r);
					   double n1 = x * d;
					   n2 = y * d;
					   double result = n1 * stddev + mean;
					   n2_cached = 1;
					   return result;
				   }
			   }
			   else
			   {
				   n2_cached = 0;
				   return n2 * stddev + mean;
			   }
		   }
	};
}