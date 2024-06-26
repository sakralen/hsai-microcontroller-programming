/*=====================================================================================*\
    Заголовочный файл ParP.h с определениями констант, макросов и прочего для программы
управления светофором.
    Для используемых при управлении светофором битов определены символические имера
NS_Pdst - вывод (и бит) управляющий зеленым светом по направлению "Север-Юг" (NS) для
пешеходов (Pedestrians), NS_Green - вывод (и бит) управляющий зеленым светом по направлению
"Север-Юг" для автомобилей и т.д.
    Для выделения группы битов, управляющих светофором, в строке 34 определена маска
SvetMask, выделяющая все эти биты.
    В строках 38, 39 - константы задержек, определяющие длительности фаз диаграммы.
При необходимости использовать ранее незадействованные биты Bit8...Bit15, для них также 
могут быть определены константы. Пока всем незадействованным битам соответствуют нулевые
константы.


\*=====================================================================================*/

    //  Константы для использованных выводов/битов порта
#define NS_Pdst     (1<<0)      //  Восемь младших битов использованы для светофора
#define NS_Green    (1<<1)
#define NS_Yellow   (1<<2)
#define NS_Red      (1<<3)

#define WO_Red      (1<<4)
#define WO_Yellow   (1<<5)
#define WO_Green    (1<<6)
#define WO_Pdst     (1<<7)      //  Секции пока не задействованы

#define Bit8        (0<<8)      //  Остальные выводы пока свободны
#define Bit9        (0<<9)
#define Bit10       (0<<10)
#define Bit11       (0<<11)

#define Bit12       (0<<12)
#define Bit13       (0<<13)
#define Bit14       (0<<14)
#define Bit15       (0<<15)

#define SvetMask    NS_Pdst|NS_Green|NS_Yellow|NS_Red|WO_Red|WO_Yellow|WO_Green|WO_Pdst

#define GR_T        20000000     //  Длительность красного или зеленого
#define YY_T         5000000     //  Длительность желтого




