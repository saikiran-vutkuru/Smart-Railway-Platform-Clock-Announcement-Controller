# Smart Railway Platform Clock & Announcement Controller

## 1. Project Overview / Purpose

The **Smart Railway Platform Clock & Announcement Controller** is an embedded railway-platform information system developed using the **LPC2148 microcontroller** and Embedded C.

The system combines a **Real-Time Clock (RTC)**, **16×2 LCD**, **4×4 matrix keypad**, **LED indicators**, **buzzer**, and an **external interrupt** to provide automatic train schedule monitoring and passenger information.

The main purpose is to:

- Display the current RTC time and date.
- Store and manage multiple train schedules.
- Compare the current RTC time with train arrival/departure timings.
- Display upcoming train information automatically.
- Provide visual status indication using LEDs.
- Provide audible alerts using a buzzer.
- Allow an administrator to edit RTC and train schedule information through an interrupt-driven keypad interface.
- Reduce the need for continuous manual platform announcements.

The project specification defines support for multiple train records and describes the system as an automatic platform information controller. The supplied implementation currently handles **three train records** through separate train variables and input/output routines.

---

## 2. Features and Functionality

| Feature | Description | Implementation |
|---|---|---|
| RTC | Maintains current time and date for schedule comparison and display. | LPC2148 RTC |
| Date & Time Display | Displays `HH:MM:SS` and `DD/MM/YYYY` on the LCD. | 16×2 LCD |
| Day Display | Displays the day abbreviation such as SUN, MON, etc. | RTC + `week[]` array |
| Train Schedule Input | Allows train number, arrival time, departure time and platform number to be entered. | 4×4 keypad |
| Multiple Trains | Supports three train records in the supplied implementation. | Train 1, Train 2, Train 3 |
| Upcoming Train Display | Displays train information when the train is within the programmed arrival window. | RTC comparison |
| 2-Minute Arrival Window | Train information is displayed beginning approximately two minutes before arrival. | `train_window()` |
| Arrival Indication | Displays an arrival message and activates the buzzer at the programmed arrival time. | `output()` |
| Departure Indication | Displays a departure message and activates the buzzer at the programmed departure time. | `output()` |
| LED Status | Uses LEDs to indicate approaching/on-time/delayed status according to the programmed counter/status logic. | GPIO LEDs |
| Buzzer Alert | Gives an audible indication during arrival/departure events. | GPIO buzzer |
| Admin Interrupt | External interrupt EINT0 enters administrator configuration mode. | VIC + EINT0 |
| Password Protection | Train configuration mode uses a password (`301` in the supplied code). | Keypad input |
| RTC Editing | Administrator can select and modify hour and minute values. | Interrupt + keypad |
| Train Editing | Administrator can modify train schedule information. | Interrupt + keypad |
| Keypad Backspace | `B` is used for backspace during numeric entry. | `ReadNum()` |
| Keypad Enter | `E` is used to accept/finish numeric input. | `ReadNum()` |
| LCD Scrolling | Train name/destination strings are scrolled across the LCD. | `output()` |
| Modular Software | LCD, keypad, delay, input, and output functions are separated into modules. | Multiple `.c`/`.h` files |

> **Implementation note:** The project PDF describes fields such as train name, destination, updated timings and delay minutes. The currently supplied source code stores train names/destinations as fixed strings in `train_output.c` and takes train number, arrival/departure times and platform number as keypad inputs.

---

## 3. Block Diagram

```text
                         +----------------------+
                         |      ADMIN USER      |
                         +----------+-----------+
                                    |
                              4×4 Matrix Keypad
                                    |
                                    v
+----------------+          +-----------------------+
|                |          |                       |
|   RTC          +--------->|                       |
| Real-Time      |          |                       |
| Clock          |          |                       |
+----------------+          |      LPC2148          |
                            |    MICROCONTROLLER     |
+----------------+          |                       |
|                |          |  - RTC Processing     |
|  EINT0         +--------->|  - Schedule Compare   |
| Admin Switch   |          |  - Keypad Processing  |
|                |          |  - LCD Control        |
+----------------+          |  - LED/Buzzer Control |
                            |                       |
+----------------+          +----+-----------+------+
| 4×4 Keypad     |               |           |
| P1.16-P1.23    +---------------+           |
+----------------+               |           |
                                 |           |
                    +------------+           +-------------+
                    |                                      |
                    v                                      v
             +-------------+                         +-------------+
             |   16×2 LCD  |                         | LED + Buzzer|
             | Passenger   |                         | Status /    |
             | Information |                         | Alert       |
             +-------------+                         +-------------+
```

### Main signal flow

```text
RTC Time
   |
   v
LPC2148
   |
   +--> Compare with Train Schedule
   |          |
   |          +--> Arrival Window --> LCD + Yellow LED
   |          |
   |          +--> Arrival Time ----> LCD + Buzzer + Status LED
   |          |
   |          +--> Departure Time --> LCD + Buzzer
   |
   +--> Normal Time/Date Display --> LCD
   |
   +--> EINT0 Interrupt --> Admin Mode --> Keypad --> Update RTC/Schedule
```

---

## 4. Flow Chart

```text
                         +----------------+
                         |     START      |
                         +-------+--------+
                                 |
                                 v
                    +-------------------------+
                    | Configure EINT0 / VIC  |
                    +-----------+-------------+
                                |
                                v
                    +-------------------------+
                    | Initialize RTC         |
                    | Set 1-second tick      |
                    +-----------+-------------+
                                |
                                v
                    +-------------------------+
                    | Initialize LCD         |
                    | Initialize Keypad      |
                    +-----------+-------------+
                                |
                                v
                    +-------------------------+
                    | Enter RTC Date/Time     |
                    | Enter Train Information |
                    +-----------+-------------+
                                |
                                v
                         +-------------+
                         |  MAIN LOOP  |
                         +------+------+
                                |
                                v
                    +-------------------------+
                    | Read current RTC        |
                    | time/date               |
                    +-----------+-------------+
                                |
                                v
                    +-------------------------+
                    | Display current time /  |
                    | date on LCD             |
                    +-----------+-------------+
                                |
                                v
                    +-------------------------+
                    | Compare RTC with Train  |
                    | Schedule                |
                    +-----------+-------------+
                                |
                    +-----------+-----------+
                    |                       |
                    v                       v
             Train in 2-min             No train
             arrival window?               |
                    |                      |
                   YES                    NO
                    |                      |
                    v                      v
             +-------------+        +-------------+
             | Display     |        | "NO TRAIN" |
             | Train Info  |        | / normal   |
             | + Yellow LED|        | display    |
             +------+------+        +-------------+
                    |
                    v
              Arrival time?
                    |
                 +--+--+
                 |     |
                YES    NO
                 |     |
                 v     |
          +-------------+ 
          | Arrival     |
          | message +   |
          | buzzer      |
          +------+------+ 
                 |
                 v
             Departure
                time?
                 |
                 v
          +-------------+
          | Departure   |
          | message +   |
          | buzzer      |
          +------+------+ 
                 |
                 v
          +-------------+
          | Repeat main |
          | loop        |
          +-------------+

          ADMIN INTERRUPT PATH
                  |
                  v
          +------------------+
          | EINT0 Triggered  |
          +--------+---------+
                   |
                   v
          +------------------+
          | Admin Menu       |
          | 1. RTC           |
          | 2. TRAIN         |
          +--------+---------+
                   |
          +--------+---------+
          |                  |
          v                  v
       RTC Edit          Train Edit
          |                  |
          v                  v
     Update Hour/Min    Password Check
                             |
                             v
                       Select Train
                             |
                             v
                  Update Schedule Data
                             |
                             v
                       Return to Main
```

---

## 5. Hardware Details

### Hardware Components

| Component | Purpose |
|---|---|
| **LPC2148** | Main microcontroller/controller |
| **16×2 LCD** | Displays RTC information and train information |
| **4×4 Matrix Keypad** | Enters RTC and train schedule information |
| **RTC peripheral** | Maintains real-time clock |
| **Green LED** | Used for normal/on-time status in the supplied output logic |
| **Yellow LED** | Indicates an approaching train |
| **Red LED** | Indicates delayed/modified train status |
| **Buzzer** | Provides audible arrival/departure indication |
| **Admin switch / EINT0** | Activates administrator configuration mode |
| **USB-UART / DB-9 cable** | Listed in the project specification for development/communication |
| **Power supply / development board** | Provides power and LPC2148 hardware platform |

### LCD Connections

The supplied `lcd_defines` and `lcd.c` files configure the LCD as an **8-bit, 2-line interface**.

| LCD Signal | LPC2148 Pin/Bit |
|---|---|
| LCD Data D0–D7 | P0.8–P0.15 |
| RS | P0.16 |
| EN | P0.17 |
| RW | P0.18 |

The LCD driver configures these pins as GPIO outputs and uses the HD44780-style commands for a 2-line LCD. 

### Keypad Connections

The supplied keypad definitions use **Port 1**:

| Keypad | LPC2148 Pin |
|---|---|
| Row 0 | P1.16 |
| Row 1 | P1.17 |
| Row 2 | P1.18 |
| Row 3 | P1.19 |
| Column 0 | P1.20 |
| Column 1 | P1.21 |
| Column 2 | P1.22 |
| Column 3 | P1.23 |

These connections are defined in `kpm_defines.h`, and the keypad driver configures the row pins and scans the four columns. 

### Keypad Layout Used in the Program

```text
+-----+-----+-----+-----+
|  1  |  2  |  3  |  E  |
+-----+-----+-----+-----+
|  4  |  5  |  6  |  B  |
+-----+-----+-----+-----+
|  7  |  8  |  9  |  -  |
+-----+-----+-----+-----+
|  C  |  0  |  =  |  +  |
+-----+-----+-----+-----+

E = Enter
B = Backspace
```

The key lookup table in the supplied `kpm.c` defines this exact mapping. 

### LED and Buzzer Connections

The output program defines:

```text
BUZZER     -> P0.21  (macro value 21)
LED_GREEN  -> P0.22  (macro value 22)
LED_RED    -> P0.23  (macro value 23)
LED_YELLOW -> P0.24  (macro value 24)
```

The source comments contain a pin-comment inconsistency for the buzzer (`#define BUZZER 21 //po.20`), so the **macro value P0.21** should be treated as the implemented connection unless the hardware wiring is intentionally different. The output code configures these GPIOs as outputs. 

### External Interrupt

The administrator switch is connected to **EINT0** through **P0.1** in the supplied `project1.c`:

```text
P0.1 -> EINT0
VIC Channel -> 14
Trigger -> Falling Edge
```

The program enables VIC channel 14, assigns the interrupt service routine to vector slot 0, and configures EINT0 as falling-edge triggered. fileciteturn0file10L27-L44

---

## 6. LCD Display with Train Details

The project uses a **16×2 LCD** to present the current time/date and train information.

### A. RTC Display

During normal operation, the main program displays:

```text
HH:MM:SS
DD/MM/YYYY
```

The day abbreviation is also displayed on the first LCD line at a later position:

```text
HH:MM:SS  MON
DD/MM/YYYY
```

The supplied code writes the RTC hour, minute, second, date, month and year directly to the LCD and uses the `week[]` array for the day abbreviation. fileciteturn0file10L70-L94

### B. Upcoming Train Display

When the current RTC time enters the train's arrival window, the LCD displays the train number and a scrolling train name/destination.

Example format:

```text
12627 KARNATAKA
P1   arr-06:30
```

The actual source uses:

- Train number on line 1.
- A scrolling train name/destination.
- Platform number on line 2.
- Arrival time in `arr-HH:MM` format.

The train display logic is implemented separately for all three trains. fileciteturn0file13L75-L119

### C. Arrival Display

At the programmed arrival time:

```text
12627 KARNATAKA
Train1 arrived
```

The buzzer is activated during the arrival indication. The corresponding status LED is selected according to the train counter/status logic. fileciteturn0file13L122-L153

### D. Departure Display

At the programmed departure time:

```text
12627 KARNATAKA
Train1 leaving
```

The buzzer is activated and the LCD shows the departure message. fileciteturn0file13L154-L185

### E. No Train Condition

When no programmed train matches the current display condition:

```text
NO TRAIN
```

is shown on the LCD. fileciteturn0file13L396-L403

### Train Information Used

The project specification provides the following example train database:

| Train | Number | Name | Destination | Scheduled Arrival | Scheduled Departure | Platform | Delay |
|---|---:|---|---|---|---|---:|---:|
| Train 1 | 12627 | Karnataka Express | New Delhi | 06:30 | 06:35 | 1 | 0 min |
| Train 2 | 12028 | Shatabdi Express | Chennai | 07:15 | 07:20 | 2 | 0 min |
| Train 3 | 12785 | Kacheguda Express | Hyderabad | 08:00 | 08:05 | 3 | 20 min |

These example records are specified in the project PDF. fileciteturn0file14L84-L110 fileciteturn0file14L112-L139

> **Important:** The current source implementation uses hardcoded strings for the displayed train names/destinations (`"Hyderabad X Gujarat"`, `"lb nagarX Hyd"`, and `"Vizag X Hyd"`), while the PDF specifies the example train database above. Therefore, the README documents both the project specification and the currently implemented display strings rather than silently treating them as identical.

---

## Software Structure

The project is divided into reusable source and header files:

```text
Smart-Railway-Platform/
│
├── project1.c
├── train_input.c
├── train_output.c
├── readnum.c
├── kpm.c
├── lcd.c
├── delay.c
│
├── input.h
├── kpm.h
├── kpm_defines.h
├── lcd.h
├── lcd_defines.h
├── defines.h
└── types.h
```

### Module Responsibilities

| File | Responsibility |
|---|---|
| `project1.c` | Main program, RTC initialization, LCD/keypad initialization and EINT0 configuration |
| `train_input.c` | RTC and train information entry |
| `train_output.c` | Train monitoring, LCD output, LEDs and buzzer control |
| `readnum.c` | Numeric keypad input, Enter and Backspace handling |
| `kpm.c` | 4×4 keypad scanning |
| `lcd.c` | LCD initialization and character/string/numeric display functions |
| `delay.c` | Microsecond, millisecond and second delay routines |
| Header files | Function declarations, pin definitions, data types and LCD/keypad macros |

The LCD module provides functions such as `InitLCD()`, `CmdLCD()`, `CharLCD()`, `StrLCD()` and numeric display functions. fileciteturn0file4L1-L10

---

## Train Arrival Detection

The implementation contains a `train_window()` function that compares the current RTC time with the programmed arrival time.

```text
Current Time
     |
     v
Calculate arrival time in minutes
     |
     v
Calculate arrival - 2 minutes
     |
     v
Is current time inside the arrival window?
     |
   +---+---+
   |       |
  YES      NO
   |       |
   v       v
Display   Continue
train     monitoring
```

The source handles the normal two-minute-before-arrival case and also contains special handling for arrival times around midnight. fileciteturn0file13L45-L73

---

## Administrator Mode

The external interrupt switches the system into administrator configuration mode.

```text
EINT0 switch pressed
        |
        v
   Admin menu
   /        \
 RTC        TRAIN
 |            |
 v            v
Edit       Password
time       verification
              |
              v
        Select Train
              |
              v
     Update train schedule
```

The supplied interrupt routine provides RTC editing and train schedule editing through the keypad. The password used in the current source is `301`. fileciteturn0file12L21-L31 fileciteturn0file12L75-L91

---

## Software and Development Tools

### Software

- **Embedded C**
- **Keil µVision / ARM7 development environment**
- **Flash Magic** for programming the microcontroller
- LPC2148 device header/library support

The project PDF lists Embedded C and Flash Magic as the software requirements. fileciteturn0file14L22-L32

### Target Controller

**NXP LPC2148 ARM7TDMI-S**

The application uses LPC21xx register-level programming for GPIO, RTC, VIC and external interrupt control.

---

## Conclusion

The Smart Railway Platform Clock & Announcement Controller demonstrates an embedded system approach to railway platform information management. It integrates RTC-based timekeeping, keypad-based schedule entry, LCD passenger information, interrupt-driven administrator control, LED status indication and buzzer alerts.

The modular design separates LCD, keypad, delay, input and train-output functionality, making the project suitable for learning and demonstrating **ARM7/LPC2148 embedded C, GPIO, RTC, keypad interfacing, LCD interfacing and external interrupts**.

