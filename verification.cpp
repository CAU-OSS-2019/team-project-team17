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
		여기까지 하면 player1, 2에 wstring으로 플레이어들 이름 들어가있는 상태야
		이 위치에서 알골 헤더안에 값 구하고
		*/
		double conformity = 3.25;
		// 셀 입력 되는지 보려고 써놓은거야 적합도를 넣어주세오
		sheet->Cell(row, 7)->Set(conformity);
	}

	xls.SaveAs("lol_list.xls");
	
	return 0;
}