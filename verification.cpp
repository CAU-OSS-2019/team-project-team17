#include "ExcelFormat.h"

using namespace ExcelFormat;

int main(int argc, char* argv[])
{
	BasicExcel xls("lol_list.xls");
	BasicExcelWorksheet* sheet = xls.GetWorksheet(0);
	XLSFormatManager fmt_mgr(xls);

	for (int row = 1; row < sheet->GetTotalRows(); row++)
	{
		BasicExcelCell* cell = sheet->Cell(row, 0);
		wstring player1 = cell->GetMyString();
		wcout.imbue(locale("kor"));
		cell = sheet->Cell(row, 2);
		wstring player2 = cell->GetMyString();
		wcout << player1<<","<< player2<<"\n";
		/*
		������� �ϸ� player1, 2�� wstring���� �÷��̾�� �̸� ���ִ� ���¾�
		�� ��ġ���� �˰� ����ȿ� �� ���ϰ�
		*/
		double conformity = 3.25;
		// �� �Է� �Ǵ��� ������ ������ž� ���յ��� �־��ּ���
		sheet->Cell(row, 7)->Set(conformity);
	}

	xls.SaveAs("lol_list.xls");
	
	return 0;
}