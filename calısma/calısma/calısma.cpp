#include <iostream>
#include <locale.h>//türkçe karakter kullanımı için kütüphane
#include <cstdlib> // rand ve srand fonksiyonları için kütüphane
#include <ctime>   // time fonksiyonu için kütüphane
#include <math.h>  //kare ve kök alma gibi matematiksel işlemler için kütüphane
using namespace std;


// Ogrenci isimli struct 
struct Ogrenci
{
	string isim, soyisim,harfnotu;
	int kisasinav1, kisasinav2, odev1, odev2, vize, final;
	float yilicinotu,gecmenotu;

};
//100 elemanlı global structure dizisi
Ogrenci ogr[100];


//rastgele kişi oluşturuken kullanılacak global string tipinde isim ve soyisim dizileri
string isimler[30] = { "can","cihan","nadir","nazan","esma","cansu","hasan","berkay","umut","ümmü","furkan","ömer","mustafa","ali","muhammet","sıla","ecem","aslı","sude","kemal","osman","nazlı","elif","irem","nil","dilara","emir","görkem","ahmet","beyza" };
string soyisimler[30] = { "örge","taş","yel","mercan","adar","salça","dal","ışıık","yılmaz","aydın","güneş","keser","öz","kara","arıkan","bektaş","aksay","bilgiç","kaya","demir","baş","yıldız","yıldırım","doğan","kılıç","gül","ateş","tekin","sarı","avcı" };

//kullanılan fonksiyonların deglerasyonu
void ogrenciolustur(int sinifmevcudu);
void ogrenciNotuOlustur(int sinifmevcudu);
void ogrenciBilgiYaz(int sinifmevcudu);
void ogrenciHarfNotu(int sinifmevcudu,float  kisa1Agirlik, float kisa2Agirlik, float odev1Agirlik, float odev2Agirlik, float vizeAgirlik, float finalAgirlik, float yiliciAgirlik);
float sinifOrtalama(int sinifmevcudu);
void standartSapma(int sinifmevcudu);
float EnBuyukNot(int sinifmevcudu);
float EnDusukNot(int sinifmevcudu);
void HarfNotuOgrenciSayısı(int sinifmevcudu);
void SinifYuzdeHesapla(int sinifmevcudu);

int main()
{
	//int tipinde değişken.Sınıf mevcudunu tutuyor
	int sinifmevcudu;
	//öğrencilerin notlarının geçme notuna etkilerini tutan değişkenler
	float  kisa1Agirlik, kisa2Agirlik,odev1Agirlik,odev2Agirlik,vizeAgirlik,finalAgirlik,yiliciAgirlik;
	//while döngüsü ile kontrol sağlamak için kullanılan değişken
	bool kontrol = false;
	//menüde switch case için seçimi tutan değişken
	char secim;
	//do while döngüsünde şartı tutan değişken
	char devammi;
	setlocale(LC_ALL, "turkish");//türkçe karakter kullanımı için
	

	cout << "öğrenci bilgi sistemine hoşgeldiniz"<<endl;

	//sınıf mevcudunun kullanıcıdan alınması ve istenilen mevcutta olup olmadığının kontrolü
	while (kontrol == false)
	{
		cout << "sinif mevcudunu giriniz:";
		cin >> sinifmevcudu;

		if (sinifmevcudu <= 100)
		{
			kontrol = true;
		}
		else
		{
			cout << "sinif mevcudu 100'den buyuk olamaz" << endl;
			kontrol = false;
		}
	}
    
	//yıliçi notların ağırlıklarının kullanıcıdan alınması ve doğru girip girilmediğinin kontrolü
	cout << "Yıliçi notlarının ağırlıklarını giriniz" << endl;
	while (kontrol==true)
	{
		cout << "1.kısa sınavın ağırlığı:";
		cin >> kisa1Agirlik;

		cout << "2.kısa sınavın ağırlığı:";
		cin >> kisa2Agirlik;

		cout << "1.ödevin ağırlığı:";
		cin >> odev1Agirlik;

		cout << "2.ödevin ağırlığı:";
		cin >> odev2Agirlik;

		cout << "vize sınavının ağırlığı:";
		cin >> vizeAgirlik;

		if (kisa1Agirlik + kisa2Agirlik + odev1Agirlik + odev2Agirlik + vizeAgirlik == 100)
		{
			kontrol = false;
		}
		else
		{
			cout << "Yıliçi notların ağırlıkları toplamı 100 olmalıdır.Lütfen ağırlıkları tekrar giriniz" << endl;
			kontrol = true;
		}
        
	}
	
	//yıliçi ve yılsonu notlarının geçme notuna etkisinin kullanıcıdan alınması ve kontrol edilmesi
	while (kontrol == false)
	{
		cout << "Yıliçi notunun geçme notuna etkisini giriniz:";
		cin >> yiliciAgirlik;

		cout << "Yılsonu notunun(final notu) geçme notuna etkisini giriniz:";
		cin >> finalAgirlik;

		if (yiliciAgirlik + finalAgirlik == 100)
		{
			kontrol = true;
		}
		else
		{
			cout << "Yıliçi ve yılsonu notların ağırlıkları toplamı 100 olmalıdır.Lütfen ağırlıkları tekrar giriniz" << endl;
			kontrol = false;
		}
	}

	//rastgele öğrenci oluşturan fonksiyon çağırılması
	ogrenciolustur( sinifmevcudu);
	//rastgele öğrenci notları oluşturan fonksiyonun çağırılması
	ogrenciNotuOlustur( sinifmevcudu);
	//rastgele oluşan notlar ile öğrencilerin harf notunu hesaplayan fonksiyonun çağırılması
	ogrenciHarfNotu(sinifmevcudu, kisa1Agirlik, kisa2Agirlik,  odev1Agirlik, odev2Agirlik,  vizeAgirlik,  finalAgirlik,  yiliciAgirlik);
	//öğrenci bilgilerini yazdıran programın çağırılması
	ogrenciBilgiYaz( sinifmevcudu);

	//do-while döngüsü
	do
 	{
		//kullanıcıya sunulan işlemler ve kullanıcı seçiminin alınması
		cout << "Yapmak istediğiniz işlemi seçiniz" << endl;
		cout << "1-sınıf ortalamasını hesapla" << endl;
		cout << "2-sınıfın standart sapmasını hesapla" << endl;
		cout << "3-sınıfın en yüksek notunu hesapla" << endl;
		cout << "4-sınıfın en düşük notunu hesapla" << endl;
		cout << "5-her bir harf notundan kaç öğrenci olduğunu hesapla" << endl;
		cout << "6-sınıfın yüzde kaçının geçip yüzde kaçının kaldığını hesapla" << endl;
		cout << " işlem:" ; cin >> secim;

		switch (secim)
		{
			//seçim 1 ise ortalama hesaplayan fonksiyon çağırılır
		case '1':
			cout << "Sınıfın ortalaması:" << sinifOrtalama(sinifmevcudu)<<endl;
			
			break;
			
		case '2':
			//seçim 2 ise standart sapma hesaplayan fonksiyon çağırılır
			standartSapma(sinifmevcudu);
			break;
		case '3':
			//seçim 3 ise sınıfın en yüksek notunu hesaplayan fonksiyon çağırılır
			cout << "Sınıfın en yüksek notu:" << EnBuyukNot(sinifmevcudu)<<endl;
		    break;
		case '4':
			//seçim 4 ise sınıfın en düşük notunu hesaplayan fonksiyon çağırılır
			cout << "Sınıfın en düşük notu:" << EnDusukNot(sinifmevcudu)<<endl;
			break;
		case '5':
			//seçim 5 ise hangi harf notundan kaç öğrenci olduğunu gösteren fonksiyon çağırılır
			HarfNotuOgrenciSayısı(sinifmevcudu);
			break;
		case '6':
			//seçim 6 ise sınıfın yüzde kaçının geçip yüzde kaçının kaldığını hesaplayan fonksiyon çağırılır
			SinifYuzdeHesapla(sinifmevcudu);
			break;
		default:
			cout << "geçerli bir işlem seçiniz"<<endl;
			break;
		}
		//kullanıcıya devam edip etmeyeği sorulur
		cout << "Başka işlem yapmak için e tuşuna çıkış yapmak için h tuşuna basınız:";
		cin >> devammi;
	} while (devammi !='h');
	
}
//rastgele öğrenci oluşturan fonksiyon
void ogrenciolustur(int sinifmevcudu)
{
	// rastgele sayı dizisi üretmek için başlangıç değeri vermemizi sağlayan fonksiyondur
	srand(time(0));
	//sınıf mevcudu kadar dönen for döngüsü
	for (int i = 0; i < sinifmevcudu; i++)
	{
		//0 ile 30 arasında rastgele sayı üretilip değişkenlere atanıyor
		int isimindex = rand() % 30;
		int soyisimindex = rand() % 30;
		//rastgele üretilen sayıyı tutan değişkenler global olarak oluşturulan string dizilerine index olarak atanıyor ve rastgele isim ve soyisim oluşuyor
		ogr[i].isim = isimler[isimindex];
		ogr[i].soyisim = soyisimler[soyisimindex];
	}
}

//rastgele öğrenci notu oluşturan fonksiyon
void ogrenciNotuOlustur(int sinifmevcudu)
{
	// rastgele sayı dizisi üretmek için başlangıç değeri vermemizi sağlayan fonksiyondur
	srand(time(0));
	// sınıfın %20sine 80 ile 100 arasında not atanması için mevcudun %20si kadar dönen for döngüsü
	for (int i = 0; i < sinifmevcudu / 5; i++)
	{
		//80 ile 100 arasında rastgele notlar atanıyor
		ogr[i].kisasinav1 = rand() % 20 + 80;
		ogr[i].kisasinav2 = rand() % 20 + 80;
		ogr[i].odev1 = rand() % 20 + 80;
		ogr[i].odev2 = rand() % 20 + 80;
		ogr[i].vize = rand() % 20 + 80;
		ogr[i].final = rand() % 20 + 80;
	}

	//sınıfın %50sine 50 ile 80 arasında not atanması için mevcudun %50si kadar dönen for döngüsü 
	for (int i = sinifmevcudu / 5; i < sinifmevcudu / 5 + sinifmevcudu / 2; i++)
	{
		//50 ile 80 arasında notlar atanıyor
		ogr[i].kisasinav1 = rand() % 30 + 50;
		ogr[i].kisasinav2 = rand() % 30 + 50;
		ogr[i].odev1 = rand() % 30 + 50;
		ogr[i].odev2 = rand() % 30 + 50;
		ogr[i].vize = rand() % 30 + 50;
		ogr[i].final = rand() % 30 + 50;
	}

	//sınıfın %30una 0 ile 50 arasında not atanması için mevcudun %30u kadar dönen for döngüsü 
	for (int i = sinifmevcudu / 2 + sinifmevcudu / 5; i < sinifmevcudu; i++)
	{
		//0 ile 50 arasında notlar atanıyor
		ogr[i].kisasinav1 = rand() % 50;
		ogr[i].kisasinav2 = rand() % 50;
		ogr[i].odev1 = rand() % 50;
		ogr[i].odev2 = rand() % 50;
		ogr[i].vize = rand() % 50;
		ogr[i].final = rand() % 50;
	}
}

//öğrencilerin bilgilerini yazdıran fonksiyon
void ogrenciBilgiYaz(int sinifmevcudu)
{
	for (int i = 0; i < sinifmevcudu; i++)
	{
		cout << "*****************************************************" << endl;
		cout << i + 1 << ". öğrenci bilgileri yazdırılıyor" << endl;
		cout << "ismi:" << ogr[i].isim << endl;
		cout << "soyisimi:" << ogr[i].soyisim << endl;
		cout << "1.kısa sınav notu:" << ogr[i].kisasinav1 << endl;
		cout << "2.kısa sınav notu:" << ogr[i].kisasinav2 << endl;
		cout << "1.ödev notu:" << ogr[i].odev1 << endl;
		cout << "2.ödev notu:" << ogr[i].odev2 << endl;
		cout << "vize notu:" << ogr[i].vize << endl;
		cout << "final notu:" << ogr[i].final << endl;
		cout << "Geçme notu:" << ogr[i].gecmenotu << endl;
		cout << "harf notu:" << ogr[i].harfnotu << endl;
		cout << "*****************************************************" << endl;
	}
}

//öğrencilerin harf notunu hesaplayan fonksiyon.Parametre olarak notların ağırlıklarını alıyor
void ogrenciHarfNotu(int sinifmevcudu,float  kisa1Agirlik,float kisa2Agirlik,float odev1Agirlik,float odev2Agirlik,float vizeAgirlik,float finalAgirlik, float yiliciAgirlik)
{
	
	for (int i = 0; i < sinifmevcudu; i++)
	{
		ogr[i].yilicinotu = ogr[i].kisasinav1 * kisa1Agirlik / 100 + ogr[i].kisasinav2 * kisa2Agirlik / 100 + ogr[i].odev1 * odev1Agirlik / 100 + ogr[i].odev2 * odev2Agirlik / 100 + ogr[i].vize * vizeAgirlik / 100;

		ogr[i].gecmenotu = ogr[i].yilicinotu * yiliciAgirlik / 100 + ogr[i].final * finalAgirlik / 100;

		//not 90 ve 100 arasında ise AA
		if (ogr[i].gecmenotu <= 100.0 && ogr[i].gecmenotu >= 90.0)
		{
			ogr[i].harfnotu = "AA";
		}
		//85 ve 89.9 arasında ise BA
		else if (ogr[i].gecmenotu <= 89.9 && ogr[i].gecmenotu >= 85.0)
		{
			ogr[i].harfnotu = "BA";
		}
		//80 ve 84.9 arasında ise BB
		else if (ogr[i].gecmenotu <= 84.9 && ogr[i].gecmenotu >= 80.0)
		{
			ogr[i].harfnotu = "BB";
		}
		//75 ve 79.9 arasında ise CB
		else if (ogr[i].gecmenotu <= 79.9 && ogr[i].gecmenotu >= 75.0)
		{
			ogr[i].harfnotu = "CB";
		}
		//65 ve 74.9 arasında ise CC
		else if (ogr[i].gecmenotu <= 74.9 && ogr[i].gecmenotu >= 65.0)
		{
			ogr[i].harfnotu = "CC";
		}
		//58 ve 64.9 arasında ise DC
		else if (ogr[i].gecmenotu <= 64.9 && ogr[i].gecmenotu >= 58.0)
		{
			ogr[i].harfnotu = "DC";
		}
		//50 ve 57.9 arasında ise DD
		else if (ogr[i].gecmenotu <= 57.9 && ogr[i].gecmenotu >= 50.0)
		{
			ogr[i].harfnotu = "DD";
		}
		//40 ve 49.9 arasında ise FD
		else if (ogr[i].gecmenotu <= 49.9 && ogr[i].gecmenotu >= 40.0)
		{
			ogr[i].harfnotu = "FD";
		}
		//0 ve 39.9 arasında ise FF
		else if (ogr[i].gecmenotu <= 39.9 && ogr[i].gecmenotu >= 0.0)
		{
			ogr[i].harfnotu = "FF";
		}
	}
	
}

//sınıfın ortalamasını hesaplayan fonksiyon
float sinifOrtalama(int sinifmevcudu)
{
	float ortalama = 0;
	float toplam = 0;

	for (int i = 0; i < sinifmevcudu; i++)
	{
		toplam += ogr[i].gecmenotu;
	}
	ortalama = toplam / sinifmevcudu;

	return ortalama;
}

//standart sapmayı hesaplayan fonksiyon
void standartSapma(int sinifmevcudu)
{
	float ort = sinifOrtalama(sinifmevcudu);
	float standartsapmaeleman;
	int standartsapma = 0;

	for (int i = 0; i < sinifmevcudu; i++)
	{
		standartsapmaeleman = ogr[i].gecmenotu - ort;
		standartsapmaeleman = standartsapmaeleman * standartsapmaeleman;
		standartsapma += standartsapmaeleman;
	}
	standartsapma = standartsapma / sinifmevcudu;
	cout << "Sınıfın standart sapması:" << sqrt(standartsapma)<<endl;

}

//en büyük notu hesaplayan(değer döndüren)fonksiyon 
float EnBuyukNot(int sinifmevcudu)
{
	float enbuyuk = ogr[0].gecmenotu;

	for (int i = 0; i < sinifmevcudu; i++)
	{
		//eğer döngü ile kontrol edilen değer enbuyuk değerden büyükse enbuyuk degerine atanır 
		if (enbuyuk < ogr[i].gecmenotu)
			enbuyuk = ogr[i].gecmenotu;
	}

	return enbuyuk;
}
//en küçük notu hesaplayan(değer döndüren)fonksiyon 
float EnDusukNot(int sinifmevcudu)
{
	float endusuk = ogr[0].gecmenotu;

	for (int i = 0; i < sinifmevcudu; i++)
	{
		//eğer döngü ile kontrol edilen değer enkucuk değerden küçükse enkucuk degerine atanır
		if (endusuk > ogr[i].gecmenotu)
			endusuk = ogr[i].gecmenotu;
	}
	return endusuk;
}

//hangi harf notunda kaç öğrenci olduğunu hesaplayan fonksiyon
void HarfNotuOgrenciSayısı(int sinifmevcudu)
{
	int sayac1=0,sayac2=0,sayac3=0,sayac4=0,sayac5=0,sayac6=0,sayac7=0,sayac8=0,sayac9 = 0;

	for (int i = 0; i < sinifmevcudu; i++)
	{
		if (ogr[i].harfnotu == "AA")
			sayac1++;
		else if (ogr[i].harfnotu == "BA")
			sayac2++;
		else if (ogr[i].harfnotu == "BB")
			sayac3++;
		else if (ogr[i].harfnotu == "BC")
			sayac4++;
		else if (ogr[i].harfnotu == "CC")
			sayac5++;
		else if (ogr[i].harfnotu == "DC")
			sayac6++;
		else if (ogr[i].harfnotu == "DD")
			sayac7++;
		else if (ogr[i].harfnotu == "FD")
			sayac8++;
		else if (ogr[i].harfnotu == "FF")
			sayac9++;

	}
	cout << "AA alan öğrenci sayısı:" << sayac1 << endl;
	cout << "BA alan öğrenci sayısı:" << sayac2 << endl;
	cout << "BB alan öğrenci sayısı:" << sayac3 << endl;
	cout << "CB alan öğrenci sayısı:" << sayac4 << endl;
	cout << "CC alan öğrenci sayısı:" << sayac5 << endl;
	cout << "DC alan öğrenci sayısı:" << sayac6 << endl;
	cout << "DD alan öğrenci sayısı:" << sayac7 << endl;
	cout << "FD alan öğrenci sayısı:" << sayac8 << endl;
	cout << "FF alan öğrenci sayısı:" << sayac9 << endl;
	
}

//sınıfın yüzde kaçının kalıp kaçının geçtiğini hesaplayan fonksiyon
void SinifYuzdeHesapla(int sinifmevcudu)
{
	int sayac1 = 0, sayac2 = 0;
	int gecen, kalan;

	for (int i = 0; i < sinifmevcudu; i++)
	{
		if (ogr[i].harfnotu == "FF" || ogr[i].harfnotu == "FD")
			sayac1++;
		else
			sayac2++;
	}
	gecen = sayac2 * 100 / sinifmevcudu;
	kalan = sayac1 * 100 / sinifmevcudu;

	cout << "Sınıfın %" << gecen << "'i geçti" << endl;
	cout << "Sınıfın %" << kalan << "'i kaldı" << endl;
}