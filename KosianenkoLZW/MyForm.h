#pragma once
#include "LZW.h"
namespace KosianenkoLZW {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: String^ file_input = "";
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(541, 46);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 33);
			this->button1->TabIndex = 0;
			this->button1->Text = L"open file";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->UseWaitCursor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(541, 129);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(240, 56);
			this->button2->TabIndex = 1;
			this->button2->Text = L"LZW compress";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->UseWaitCursor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(541, 273);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(240, 38);
			this->button3->TabIndex = 2;
			this->button3->Text = L" Check compressed file";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->UseWaitCursor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Location = System::Drawing::Point(541, 330);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(240, 33);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Check decompressed file";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->UseWaitCursor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(84, 46);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(435, 33);
			this->textBox1->TabIndex = 4;
			this->textBox1->UseWaitCursor = true;
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(82, 108);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(437, 255);
			this->textBox2->TabIndex = 5;
			this->textBox2->UseWaitCursor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(855, 405);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->UseWaitCursor = true;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		BFILE* OpenOutputBFile(char* name)
		{
			BFILE* bfile;

			bfile = (BFILE*)calloc(1, sizeof(BFILE));
			bfile->file = fopen(name, "wb");
			bfile->rack = 0;
			bfile->mask = 0x80;
			bfile->pacifier_counter = 0;
			return bfile;
		}

		/*-----------------------------------------------------------
		   �������� ����� ��� ���������� ������
		*/

		BFILE* OpenInputBFile(char* name)
		{
			BFILE* bfile;

			bfile = (BFILE*)calloc(1, sizeof(BFILE));
			bfile->file = fopen(name, "rb");
			bfile->rack = 0;
			bfile->mask = 0x80;
			bfile->pacifier_counter = 0;
			return bfile;
		}

		/*-----------------------------------------------------------
		   �������� ����� ��� ��������� ������
		*/

		void CloseOutputBFile(BFILE* bfile)
		{
			if (bfile->mask != 0x80)
				putc(bfile->rack, bfile->file);
			fclose(bfile->file);
			free((char*)bfile);
		}

		/*-----------------------------------------------------------
		   �������� ����� ��� ���������� ������
		*/

		void CloseInputBFile(BFILE* bfile)
		{
			fclose(bfile->file);
			free((char*)bfile);
		}

		/*-----------------------------------------------------------
		   ����� ������ ����
		*/

		void WriteBit(BFILE* bfile, int bit)
		{
			if (bit)
				bfile->rack |= bfile->mask;
			bfile->mask >>= 1;
			if (bfile->mask == 0)
			{
				putc(bfile->rack, bfile->file);
				if ((bfile->pacifier_counter++ & PACIFIER_COUNT) == 0)
					putc('.', stdout);
				bfile->rack = 0;
				bfile->mask = 0x80;
			}
		}

		/*-----------------------------------------------------------
		   ����� ���������� �����
		*/

		void WriteBits(BFILE* bfile, unsigned long code, int count)
		{
			unsigned long mask;

			mask = 1L << (count - 1);
			while (mask != 0)
			{
				if (mask & code)
					bfile->rack |= bfile->mask;
				bfile->mask >>= 1;
				if (bfile->mask == 0)
				{
					putc(bfile->rack, bfile->file);
					if ((bfile->pacifier_counter++ & PACIFIER_COUNT) == 0)
						putc('.', stdout);
					bfile->rack = 0;
					bfile->mask = 0x80;
				}
				mask >>= 1;
			}
		}

		/*-----------------------------------------------------------
		   ���� ������ ����
		*/

		int ReadBit(BFILE* bfile)
		{
			int value;

			if (bfile->mask == 0x80)
			{
				bfile->rack = getc(bfile->file);
				if (bfile->rack == EOF)
					printf("Error in ReadBit_func\n");//fatal_error( "Error in function ReadBit!\n" );
				if ((bfile->pacifier_counter++ & PACIFIER_COUNT) == 0)
					putc('.', stdout);
			}

			value = bfile->rack & bfile->mask;
			bfile->mask >>= 1;
			if (bfile->mask == 0)
				bfile->mask = 0x80;
			return (value ? 1 : 0);
		}

		/*-----------------------------------------------------------
		   ���� ���������� �����
		*/

		unsigned long ReadBits(BFILE* bfile, int bit_count)
		{
			unsigned long mask;
			unsigned long return_value;

			mask = 1L << (bit_count - 1);
			return_value = 0;
			while (mask != 0)
			{
				if (bfile->mask == 0x80)
				{
					bfile->rack = getc(bfile->file);
					if (bfile->rack == EOF)
						printf("Error in ReadBits_func\n");// fatal_error( "Error in function ReadBits!\n" );
					if ((bfile->pacifier_counter++ & PACIFIER_COUNT) == 0)
						putc('.', stdout);
				}
				if (bfile->rack & bfile->mask)
					return_value |= mask;
				mask >>= 1;
				bfile->mask >>= 1;
				if (bfile->mask == 0)
					bfile->mask = 0x80;
			}

			return return_value;
		}

		/*-----------------------------------------------------------
		   ����� ��������� �� �������������
		*/

		void usage_exit()
		{
			printf("\n Using: %s e|d infile outfile\n", compressor_filname);
			printf("e - for encoding (compression)\n");
			printf("d - for decoding (decompression)\n");
			exit(0);
		}

		/*-----------------------------------------------------------
		   ��������� ������� �����
		*/

		/*-----------------------------------------------------------
		   ����� ��������� � ����������� �������� ������
		*/


		/*-----------------------------------------------------------
																	   ����� ���������� �������� ����� ���������� ��������� LZW
		*/

	
		/*-----------------------------------------------------------
		   ��������� ������ �����
		*/

		void CompressFile(FILE* input, BFILE* output)
		{
			int next_code, character, string_code;
			unsigned int index, i;

			/* ������������� */
			next_code = FIRST_CODE;
			for (i = 0; i < TABLE_SIZE; i++)
				dict[i].code_value = UNUSED;
			/* ������� ������ ������ */
			if ((string_code = getc(input)) == EOF)
				string_code = END_OF_STREAM;
			/* ���� �� ����� ��������� */
			while ((character = getc(input)) != EOF)
			{
				/* ������� ����� � ������� ���� <�����, ������> */
				index = find_dictionary_match(string_code, character);
				/* ������������ ������� */
				if (dict[index].code_value != -1)
					string_code = dict[index].code_value;
				/* ����� ���� � ������� ��� */
				else
				{
					/* ���������� � ������� */
					if (next_code <= MAX_CODE)
					{
						dict[index].code_value = next_code++;
						dict[index].prefix_code = string_code;
						dict[index].character = (char)character;
					}
					/* ������ ���� */
					WriteBits(output, (unsigned long)string_code, BITS);
					string_code = character;
				}
			}
			/* ���������� ����������� */
			WriteBits(output, (unsigned long)string_code, BITS);
			WriteBits(output, (unsigned long)END_OF_STREAM, BITS);
		}

		/*-----------------------------------------------------------
		   ��������� ������������� ������� �����
		*/

		void DecompressFile(BFILE* input, FILE* output)
		{
			unsigned int next_code, new_code, old_code;
			int character;
			unsigned int count;

			next_code = FIRST_CODE;
			old_code = (unsigned int)ReadBits(input, BITS);
			if (old_code == END_OF_STREAM)
				return;
			character = old_code;

			putc(old_code, output);

			while ((new_code = (unsigned int)ReadBits(input, BITS))
				!= END_OF_STREAM)
			{
				/* ��������� ��������� �������������� �������� */
				if (new_code >= next_code)
				{
					decode_stack[0] = (char)character;
					count = decode_string(1, old_code);
				}
				else
					count = decode_string(0, new_code);

				character = decode_stack[count - 1];
				/* ������ ��������������� ������ */
				while (count > 0)
					putc(decode_stack[--count], output);
				/* ���������� ������� */
				if (next_code <= MAX_CODE)
				{
					dict[next_code].prefix_code = old_code;
					dict[next_code].character = (char)character;
					next_code++;
				}
				old_code = new_code;
			}
		}

		/*-----------------------------------------------------------
		   ��������� ������ � ������� ��������� ���� <��� �����,
		   ������>. ��� ��������� ������ ������������ ���, ����������
		   �� ����������.
		*/

		unsigned int find_dictionary_match(int prefix_code, int character)
		{
			int index;
			int offset;

			/* ���������� ��������� �������� ���-������� */
			index = (character << (BITS - 8)) ^ prefix_code;
			/* ���������� ��������� �������� */
			if (index == 0)
				offset = 1;
			else
				offset = TABLE_SIZE - index;
			for (; ; )
			{
				/* ��� ������ ������� �� ������������ */
				if (dict[index].code_value == UNUSED)
					return index;
				/* ������� ������������ */
				if (dict[index].prefix_code == prefix_code && dict[index].character == (char)character)
					return index;
				/* ��������. ���������� � ��������� ������� ��
				   ���������� */
				index -= offset;
				if (index < 0)
					index += TABLE_SIZE;
			}
		}

		/*-----------------------------------------------------------
		   ��������� ������������� ������. ��������� ������� � �����,
		   ���������� �� ����������.
		*/

		unsigned int decode_string(unsigned int count, unsigned int code)
		{
			while (code > 255) /* ���� �� ���������� ��� ������� */
			{
				decode_stack[count++] = dict[code].character;
				code = dict[code].prefix_code;
			}
			decode_stack[count++] = (char)code;
			return count;
		}

		void SysStringToString(String^ s, std::string& os)
		{
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void LZWAlgorithm(String^ filename) 
		{
			setbuf(stdout, NULL);

			// � ������ ������������� ���������� ����������
			// ��������� ������ ������������� ���������

		   /////////////////////////////////////////////////////////////
			//if (argc < 4)
			// usage_exit();

			// ����������:
			//if (argv [1] [0] == 'e' || argv [1] [0] == 'E')
			//{
			BFILE* output;
			FILE* input;
			std::string fname = "";
			SysStringToString(filename, fname);
			// �������� �������� ����� ��� ������
			input = fopen(fname.c_str(), "rb");
			if (input == NULL)
				printf("Err op file\n");// fatal_error( "������ ��� �������� %s ��� �����\n", argv[ 2 ] );
			
				// �������� ��������� ����� ��� ������
			output = OpenOutputBFile("Compressed_output.txt");
			if (output == NULL)
				printf("Err open file\n");//fatal_error( "������ ��� �������� %s ��� ������\n", argv[ 3 ] );
		

			// ����� ��������� ����������
			CompressFile(input, output);

			// �������� ������
			CloseOutputBFile(output);
			fclose(input);

			printf("\nCompression complete.");

			// ����� ������������ ������
		   //}
		   // ������������:
		   //else if (argv [1] [0] == 'd' || argv [1] [0] == 'D')
		   //{
			BFILE* in;
			FILE* out;

			// �������� �������� ����� ��� ������
			in = OpenInputBFile("Compressed_output.txt");
			if (in == NULL)
				printf("Err open file2\n");//fatal_error( "Error on open %s for read\n", argv[ 2 ] );

			   // �������� ��������� ����� ��� ������
			out = fopen("Readable_output.txt", "wb");
			if (out == NULL)
				printf("Err out file open\n");//fatal_error( "Error on open %s for write\n", argv[ 3 ] );

			printf("\nDecompression %s into %s\n", "out.txt", "full_out.txt");

			// ����� ��������� ������������
			DecompressFile(in, out);

			// �������� ������
			CloseInputBFile(in);
			fclose(out);

			printf("\nDecompression complete.");
			// };

			return;


		}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		String^ file_name = "";
		if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			file_name = openFileDialog1->FileName;
		}

			textBox1->Text = file_name;
			file_input = file_name;
			button2->Enabled = true;
	}
	
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LZWAlgorithm(file_input->ToString());
		button3->Enabled = true;
		button4->Enabled = true;
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		textBox2->Text = "";
		StreamReader^ reader = File::OpenText("Compressed_output.txt");
		textBox2->Text = reader->ReadToEnd();
		reader->Close();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		textBox2->Text = "";
		StreamReader^ reader = File::OpenText("Readable_output.txt");
		textBox2->Text = reader->ReadToEnd();
		reader->Close();
	}


};
}
