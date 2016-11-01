#pragma once
#include"Lib.h"
class ThongTinChiTieu
{
	WCHAR *bffLoaiChiTieu;
	WCHAR *bffNoiDungChiTieu;
	WCHAR *bffSoTienChiTieu;
public:
	ThongTinChiTieu(){
		bffLoaiChiTieu = new WCHAR[256];
		bffNoiDungChiTieu = new WCHAR[256];
		bffSoTienChiTieu = new WCHAR[20];
	}
	~ThongTinChiTieu(){
		delete bffLoaiChiTieu;
		delete bffNoiDungChiTieu;
		delete bffSoTienChiTieu;
	}
	void readFile(wfstream f){
		
	}
	void writeFile(wfstream f){
		wstring text =
			L"< ?xml version=\"1.0\" encoding=\"UTF-8\"? >\n"
			L"< root description=\"this is a naïve example\" >\n< /root >";
		f << text;
		f << (wstring)bffLoaiChiTieu;
	}
};

