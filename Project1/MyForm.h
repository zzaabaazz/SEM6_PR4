#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <random>

#define N 1000 // Длительность входной реализации смеси сигнала с шумом в шагах дискретизации
#define L1 500 // Длительность сигнала и импульсной характеристики согласованного фильтра в шагах дискретизации
#define L2 700 


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
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(575, 287);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &MyForm::chart1_Click);
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
		//help

		// Полезный сигнал, импульсная характеристика, входная реализация, выходная реализация
		array<double>^ x = gcnew array<double>(N);
		array<double>^ y = gcnew array<double>(N);
		array<double>^ k = gcnew array<double>(N);
		array<double>^ s = gcnew array<double>(N);
		int i, p, n;

		// Формирование входного сигнала
		for (i = 0; i < N; i++) {
			s[i] = exp(-3 * i);
			x[i] = s[i];
		}
		float delta1,delta2;
		//  Формирование импульсной характеристики
		for (i = 0; i < N; i++) {
			k[i] = ((i == L2) ? 1 : 0) + ((i == L1) ? 1 : 0);
		}

		// Добавление шума ко входной реализации
		for (i = 0; i < N; i++) {
			x[i] = x[i] + gauss(0, 0.5);
		}

		// Согласованная фильтрация
		for (i = 0; i < N; i++) {
			y[i] = 0.0;
			for (p = 0; p < N; p++) { //я изменил p > L тк не выполняется
				if ((i - p) >= 0) {
					y[i] = y[i] + x[i - p] * k[p];
				}
			}
		}

		for (int n = 0; n < N; n++) {
			chart1->Series[0]->Points->AddXY(n, y[n]);

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
