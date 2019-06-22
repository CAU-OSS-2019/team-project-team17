#include "ExcelFormat.h"
#include <string>
#include <locale>
#include <vector>

using namespace ExcelFormat;

string wcs_to_mbs(wstring const& str, locale const& loc)
{
	typedef codecvt<wchar_t, char, mbstate_t> codecvt_t;

	std::codecvt<wchar_t, char, std::mbstate_t> const& codecvt = std::use_facet<codecvt_t>(loc);

	std::mbstate_t state = std::mbstate_t();

	std::vector<char> buff((str.size() + 1) * codecvt.max_length());

	wchar_t const* in_next = str.c_str();

	char* out_next = &buff[0];

	codecvt_t::result r = codecvt.out(state, str.c_str(), str.c_str() + str.size(), in_next, &buff[0], &buff[0] + buff.size(), out_next);

	return std::string(&buff[0]);
}

int main(int argc, char* argv[])
{
	BasicExcel xls("lol_list.xls");
	BasicExcelWorksheet* sheet = xls.GetWorksheet(0);
	XLSFormatManager fmt_mgr(xls);

	for (int row = 1; row < sheet->GetTotalRows(); row++)
	{
		wcout.imbue(locale("kor"));
		std::locale loc("kor");

		BasicExcelCell* cell = sheet->Cell(row, 0);

		wstring wplayer1 = cell->GetMyString();
		string player1;
		player1 = wcs_to_mbs(wplayer1, loc);

		cell = sheet->Cell(row, 2);
		wstring wplayer2 = cell->GetMyString();
		string player2;
		player2 = wcs_to_mbs(wplayer2, loc);

		cout << player1 << "," << player2 << "\n";
		/*

		TODO: ������� �ϸ� player1, 2�� wstring���� �÷��̾�� �̸� ���ִ� ���¾�
		�� ��ġ���� �˰� ����ȿ� �� ���ϰ�

		*/
		double conformity = 3.25;
		// �� �Է� �Ǵ��� ������ ������ž� ���յ��� �־��ּ���
		sheet->Cell(row, 7)->Set(conformity);
	}

	xls.SaveAs("lol_list.xls");
	
	return 0;
}