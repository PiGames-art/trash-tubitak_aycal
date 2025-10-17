#include <Servo.h>
#hahadeneneme

// Servo motoru nesnelerini oluşturuyoz
Servo servo1;
Servo servo2;
// Ultrasonik sensör pinleri. Bunları devre kartında nereye bağladığımıza göre değiştireceğiz.
const int trigPin = 9;
const int echoPin = 8;
// Servo pinleri. Bunlarıda değiştireceğiz.
const int servo1Pin = 5;
const int servo2Pin = 6;

// Servo açıları
int servo1Normal = 0;
int servo2Normal = 0;
int servo1Aktif = 90;
int servo2Aktif = 90;

// Normalde uzunluk değeri(cm). Bunu, kutuya göre deeğiştireceğiz.
const int VarsayılanMesafe = 20;
// Sensörün uzunluk ölçmesi için değişkenler atıyoz
long sure;
int mesafe;
void setup() {
  Serial.begin(9600);
  // Pin yönleri
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Servoları başlat
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // Servoları başlangıç konumuna getir
  servo1.write(servo1Normal);
  servo2.write(servo2Normal);
}void loop() {
  // Uzaklığı ölçüyo
  mesafe = uzaklikOlc();
  /*
  * Serial.print("Uzaklik: ");
  * Serial.print(mesafe);
  * Serial.println(" cm");
  * Bunlar aslında sadece test etmek için. Yoksa gerekli değiller normalde.
  */
  // Eğer belirlenen mesafeden daha yakınsa
  if (mesafe > 0 && mesafe < VarsayılanMesafe) {
    servo1.write(servo1Aktif);
    servo2.write(servo2Aktif);
  } else {
    // Uzaklık normale döndüyse
    servo1.write(servo1Normal);
    servo2.write(servo2Normal);
  }
  /*
   * İşin asıl kısmı burası. Burada "Eğerki varsayılan uzunluktan kısaysa, motoru çalıştır;
   * Eğerki varsayılan uzunluktaysa motoru eski haline döndür."
   * Tabi bu loop(döngü) değişkeninde olduğundan sürekli tekrarlanacak. Bir sıkıntı yok yaniii :D
   * Tabi C++ tuhaf bir dil. Sıkıntıda çıkabilir. Valla lisanstada yazıyor garanti yok diye. Haberiniz olsun!
   */
  delay(200); // Ne kadar sürede bir ölçüm yapacağı. Sürekli sensörü gebertmesini istiyorsak bunu silebiliriz.
}

int uzaklikOlc() {
  // Trig pinine kısa bir sinyal gönder
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo pininden süreyi oku
  vakit = pulseIn(echoPin, HIGH);

  // Ses hızı: 34300 cm/s, gidiş-dönüş için 2'ye böl
  int mesafe = vakit * 0.034 / 2;
  return mesafe;
}

