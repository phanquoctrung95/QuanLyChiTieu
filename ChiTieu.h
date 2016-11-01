#pragma once
#include"Lib.h"
class ChiTieu
{
	WCHAR *_Loai;
	WCHAR *_NoiDung;
	WCHAR *_SoTien;
public:
	ChiTieu(){
		_Loai = new WCHAR[MAXLEN];
		_NoiDung = new WCHAR[MAXLEN];
		_SoTien = new WCHAR[MAXLEN];
	}
	~ChiTieu(){
		//delete _Loai;
		//delete _NoiDung;
		//delete _SoTien;
	}
	void setLoai(WCHAR *x){
		wcscpy(_Loai, x);
	}
	void setNoiDung(WCHAR *x){
		wcscpy(_NoiDung, x);
	}
	void setSoTien(WCHAR *x){
		wcscpy(_SoTien, x);
	}
	WCHAR *getLoai(){
		return _Loai;
	}
	WCHAR *getNoiDung(){
		return _NoiDung;
	}
	WCHAR *getSoTien(){
		return _SoTien;
	}
};

