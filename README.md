# Final_Project &#x1F60D;&#x1F60D;&#x1F60D;&#x1F60D;&#x1F60D;&#x1F4AF;&#x1F4AF;&#x1F4AF;

## Basic Part
### Data Type and Data Structure
&#x2705; Your database system needs to have at least three basic data types.

&#x2705; There should be at least one data with the string type in the system.

&#x2705; There should be at least one kind of data created using structure, union, or enumerations.

&#x2705; You need to use at least a linked list to store some data in your database system.

## Operation

### Add
&#x2705; Add a new item to the database system. **The program must print an error message if**
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

&#x2705; Gender&emsp;(int)

&#x2705; Age&emsp;(int)

&#x2705; Height&emsp;(float)

&#x2705; Zodiac&emsp;(string)

&#x2705; income&emsp;(int)

&#x2705; job&emsp;(string)

### Pairing Mechanism
- [ ] A good-looking interface

&#x2705; A bottom to choose whether you like the person

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
    int score;
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

<img src="picture/Taiwan_all.png">

### 昱人的小空間
* fileIO.c 
  * 1.0.1
    * 加了讀縣市距離的編號, 還有執行時間
* add.c
  * 1.0.0
    * 添加相同電話號碼會發現
    * 選興趣的按鈕，Cool(WASD 或 上下左右)
    * 最後印出有很多顏色的個人資料給他確認，看要不要重新輸入
    * 如果要玩玩看的話背景用深色高對比或白色的主題那個顯示出來的顏色會比較正常
    * 啊我不知道Mac的顏色跑不跑的出來
  * 1.0.1
    * Data person[1000]丟到全域
  * 1.0.2
    * 跟add_plus_sort 的 add 一樣 
* add_plus_sort
  * 1.0.0
    * 順序已經排出來了, 但還不行只讓圈內人顯示出來就好
  * 1.0.3
    * 差不多好了，選到20個人也會停，差我的invalid input
    * 邱哥如果要接下去的話，應該要讓它把他喜歡的20人串成一個linked list, 我們現在只有讓他喜歡 不會把它串起來
  * 1.0.5
    * 接近完美版，都可以知道有沒有輸入錯誤 只差興趣多加一點 把按鈕文字丟到函式裡面 省個空間
  * 1.0.6
    * 讀的時候把縣市編號存進去
    * Zodiac, City, Income 改用按鈕選擇
  * 1.0.7
    * 創好的帳號會輸出到txt裡面
    * 興趣改成50個 基本上我的部分好了 🐬🐬🐬🐬🐬🐬🐬🐬🐬🐬

### 柯的
* fileIO.c
  * 新增score變數
* display_order
  * 1.0.1
    * 把Data person移到全域了，用qsort比較方便
    * 我沒有用linked list，因為一開始用陣列存就是連續記憶體了，覺得沒必要用到
    
    <img src="picture/relationship.jpg">

  * 1.0.2
    * 小小修改
  * 1.0.3
    * 顯示順序出來了剩下漂亮的排版和做YES/NO鍵
  * 1.0.4
    * 好了耶！還是覺得排版醜醜的，還有不確定滑完會發生什麼事，應該沒事啦～
* add_plus_sort
  * 1.0.1
    * 前半部需要修改的有
      * file的地區賦值
      * 輸錯資訊的應對措施
      * 漂亮排版
  * 1.0.2
    * 比對hobbies(和area)換成strcasecmp避免資料一開始大小寫就不一樣
  * 1.0.4
    * search 的部分都好了，多加了一個preference的部分，可喜可賀！
### 邱
* add_plus_sort2
  * 1.0.0
    * 目前可以把20個喜歡的人存進鏈結裡面
    * 能隨機選5個人存到另一條鏈結裡面
* 然後因為不是window系統，我把conio.h windows.h換成別的函式庫，裡面有小改一點，但功能一樣
* 抱歉檔名取的很懶

### 婕
* with_change_mode
  * 1.0.0
    * 把add_plus_sort2加上換模式
    * 但是選擇繼續配對的話會跳出一樣的人，等等再改
    * user最喜歡的人的資料會被output到final_decision.txt

* aps1.0.6_with_mode
  * 1.0.1
    * 把add_plus_sort 1.0.6加上配對和換模式（mac版本）
    * 交出20人之後，重新進去display的時候還是會顯示一樣的人，看不出問題在哪><
    * '\r'的部分都用'\t'代替了，因為mac讀不了\r，統整的時候再改回來
    * 有時候配對好像沒有成功，有些人的資料顯示不出來！
    * 目前沒看到之前討論的喜歡滿20人可以選擇交出20人名單或是可以把一些人數喜歡的list刪掉的部分
### 彬
* 1.0.0
    * read_file() 可以選檔案不過會蓋掉之前的檔案可能要寫個add_file()
    * write_file() 在想要不要可以輸入條件然後只印男的或幾歲以下
    * sort() 先這樣可能可以加上遞增遞減排序
    * 其他basic part 和 login 基本是完成了
    * 文字UI難產