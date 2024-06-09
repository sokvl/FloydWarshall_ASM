#pragma once
#include <iostream>
#include <string>
#include "Controller.h"
#include <chrono>
#include <vector>
#include <thread>

#include <msclr/marshal_cppstd.h>

namespace winfrom {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Podsumowanie informacji o MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
			
		}

	protected:
		/// <summary>
		/// Wyczyść wszystkie używane zasoby.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: Controller ctr;
	private: System::Windows::Forms::Button^ button1;
	private: int a = 0;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;

	private: System::Windows::Forms::Label^ ThreadLabel;
	private: System::Windows::Forms::Button^ button3;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ThreadLabel = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(79, 60);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(536, 448);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellContentClick);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(93, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Run";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(578, 18);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(44, 17);
			this->radioButton1->TabIndex = 5;
			this->radioButton1->Text = L"C++";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Location = System::Drawing::Point(628, 18);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(48, 17);
			this->radioButton2->TabIndex = 6;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"ASM";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MainForm::radioButton2_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(76, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Output:";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(167, 600);
			this->trackBar1->Maximum = 64;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(333, 45);
			this->trackBar1->TabIndex = 8;
			this->trackBar1->Value = std::thread::hardware_concurrency();
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MainForm::trackBar1_Scroll);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(148, 600);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(13, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"1";
			this->label2->Click += gcnew System::EventHandler(this, &MainForm::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(506, 600);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(19, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"64";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(311, 575);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 13);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Threads:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Load File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(263, 551);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(79, 13);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Execution time:";
			this->label5->Click += gcnew System::EventHandler(this, &MainForm::label5_Click);
			// 
			// ThreadLabel
			// 
			this->ThreadLabel->AutoSize = true;
			this->ThreadLabel->Location = System::Drawing::Point(367, 575);
			this->ThreadLabel->Name = L"ThreadLabel";
			this->ThreadLabel->Size = System::Drawing::Size(13, 13);
			this->ThreadLabel->TabIndex = 15;
			this->ThreadLabel->Text = std::thread::hardware_concurrency().ToString();
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(349, 551);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(75, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Run algorithm!";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(694, 665);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->ThreadLabel);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Location = System::Drawing::Point(348, 551);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::WindowsDefaultBounds;
			this->Text = L"Floyd-Warshall";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Stream^ myStream;
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "txt files (*.txt)|*.txt";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;
	
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if ((myStream = openFileDialog1->OpenFile()) != nullptr) {

				System::String^ filePath = openFileDialog1->FileName;
				// Konwertuj System::String na std::string
				std::string filePathStd = msclr::interop::marshal_as<std::string>(filePath);

				std::vector<signed> temp = ctr.loadGraph(filePathStd);
				ctr.setGraphFromVector(temp);

				signed int* tab = ctr.getGraph();

				myStream->Close();
			}
		}

	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		
		if (ctr.getGraph() == nullptr) {
			return;
		}

		auto duration = ctr.runFloydWarshall(ctr.getMode(), ctr.getThreads());

		label6->Text = duration.count().ToString() + " [us]";

		signed* tab = ctr.getGraph();

		int n = ctr.getN();
		if (n < 11) {

			dataGridView1->ColumnCount = n;
			dataGridView1->RowCount = n;

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					int index = i * n + j; // Przekształć indeksy w jednowymiarowej tablicy na odpowiedni indeks
					dataGridView1->Rows[i]->Cells[j]->Value = tab[index].ToString();
					dataGridView1->Columns[i]->HeaderText = (i + 1).ToString();
					dataGridView1->Rows[i]->HeaderCell->Value = (i + 1).ToString();
				}
			}
		}
		dataGridView1->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders);
		dataGridView1->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
		dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::AllCells;
		

	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
		int currVal = trackBar1->Value;
		ctr.setSliderValue(currVal);
		ThreadLabel->Text = currVal.ToString();

	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}

	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		ctr.setMode(false);
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		ctr.setMode(true);
	}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
