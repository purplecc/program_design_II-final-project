# Final_Project &#x1F60D;&#x1F60D;&#x1F60D;&#x1F60D;&#x1F60D;&#x1F4AF;&#x1F4AF;&#x1F4AF;

## Basic Part
### Data Type and Data Structure
&#x2705; Your database system needs to have at least three basic data types.

&#x2705; There should be at least one data with the string type in the system.

&#x2705; There should be at least one kind of data created using structure, union, or enumerations.

&#x2705; You need to use at least a linked list to store some data in your database system.

## Operation

### Add
- [ ] Add a new item to the database system. **The program must print an error message if**
**the item is already in the database.**
### Delete
- [ ] Delete a given item from the database. **The program must print an error message if**
**there is no matching item to be deleted in the database.**
### Traverse
- [ ] Print all items in the database in a specific format.
### Search
- [ ]  Given certain information about the item, the program needs to find and print the
specific item.
### Sort
- [ ] Sort all the items in ascending or descending order according to the given data. 
For example, you can sort products by their prices or expired dates.
### File I/O
&#x2705; Users can import items to the database system from external files and they can also export files of outputs or selected items into files. You can design the special file format for the database system.

## Advance Part
### ?????????????????????????????????????????????????

## Method

### SORT **(Use qsort)**
- [ ] Distance&emsp;(int)
  * set coordinates and count
- [ ] Gender&emsp;(int)
- [ ] Age&emsp;(int)
- [ ] Height&emsp;(float)
- [ ] Zodiac&emsp;(string)
- [ ] income&emsp;(int)
- [ ] job&emsp;(string)

### Pairing Mechanism
- [ ] A good-looking interface

- [ ] A bottom to choose whether you like the person

- [ ] 25 people like the **USER** after entering the information (random)

> mode

- [ ] Match mode

- [ ] Chat mode

- [ ] Exit app

### Display Order **(Use linked list)**
* Sexuality
* Does that guy like me
* Distance
* Hobby

**_同分就Random_**
* The length limit of the list of the person you like is 20 every day
  * Person you like
  * Can chat
  * Show the person I like, if someone you don't like anymore, you can delete him

### Paired Successfully
* Pop the pairing success message up and all information of each other
* Show the phone number to each other

## To do (5/10)

### Write character information
* Each group member must write 155 people's information
  * man 50 people
  * woman 50 people
  * lesbian 25 people
  * gay 25 people
  * bisexual 5 people
* Phone number's third value (Ex.09***1***0502291)
  * 林子婕 0~1
  * 柯宸瑀 2~3
  * 蔡維彬 4~5
  * 王昱人 6~7
  * 邱義咸 8~9

### Txt Format
```C
typedef struct data{
    char name[21];                  // txt用空格切, 照順序打下來, 整個人的資訊打完再換行
    char gender;                    // 單字中間有空格用 '-' 代替
    char hobby[5][36];              // 最後輸入自我介紹的時候有空格沒關係
    char phone_number[11];          // 打完再按Enter
    char area[16];
    char target;                    // 雙性戀填'B'喔🐉🐉🐉🐉🐉
    int age;
    float height;
    char zodiac[21];
    char income[11];
    char job[41];
    int index_of_area;
    char self_introduction[151];
} Data;
```

### Example
```
*  名字	 John
*  性別	 Male
*  興趣	 Shopping, Brunch, Memes, Motorcycling, Acapella
*  手機號碼  0910000001
*  生活地區  嘉義市
*  目標性別  Female
*  年紀	 23
*  身高	 175.2
*  星座	 Aquarius
*  收入	 <100, 100~300, 300~500, >500  //變這樣可以嗎 🔍🔍🔍
*  工作	 學生
*  自我介紹
*  少座標 之後想怎麼算距離
```
</br>
<table>
    <tr>
    <td><h2 style="margin:0px; padding:5px 390px 5px 5px; ">Zodiac</h2></td>
    <td><h2 style="margin:0px; padding:5px 390px 5px 5px;">Cities</h2></td>
    </tr>
    <tr>
      <td>
        <ul>
          <br/> <li>&#x2651; Capricorn</li><br/>
          <li>&#x2652; Aquarius</li><br/>
          <li>&#x2653; Pisces</li><br/>
          <li>&#x2648; Aries</li><br/>
          <li>&#x2649; Taurus</li><br/>
          <li>&#x264A; Gemini</li><br/>
          <li>&#x264B; Cancer</li><br/>
          <li>&#x264C; Leo</li><br/>
          <li>&#x264D; Virgo</li><br/>
          <li>&#x264E; Libra</li><br/>
          <li>&#x264F; Scorpio</li><br/>
          <li>&#x2650; Sagittarius</li><br/>
        </ul>
      </td>
      <td>
        <ul>
          <li>&#x1F308; Keelung
          <li>&#x1F309; New-Taipei
          <li>&#x1F30A; Taipei
          <li>&#x1F30B; Taoyuan
          <li>&#x1F30C; Hsinchu
          <li>&#x1F30F; Miaoli
          <li>&#x1F42C; Taichung
          <li>&#x1F47D; Changhua
          <li>&#x1F314; Nantou
          <li>&#x1F4A6; Yunlin
          <li>&#x1F320; Chiayi
          <li>&#x1F331; Tainan
          <li>&#x1F337; Kaohsiung
          <li>&#x1F33A; Pingtung
          <li>&#x1F33B; Yilan
          <li>&#x1F33C; Hualien
          <li>&#x1F33D; Taitung
          <li>&#x1F341; Penghu
          <li>&#x1F41B; Kinmen
          <li>&#x1F427; Lienchiang
        </ul>
      </td>
    </tr>
  </table>  

<img src="Taiwan.png">

### 昱人的小空間
* 1.0.1 fileIO.c 加了讀縣市距離的編號, 還有執行時間