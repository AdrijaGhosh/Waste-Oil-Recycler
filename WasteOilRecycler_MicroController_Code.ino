// Define the pins
const int pump1rly1Pin = PA0; //1 // Enable pin for the 1st pump
const int pump2rly2Pin = PA1; //2 //IN pin for the 1st pump
//const int vacuumPump1rly3Pin = PA2; //3 // Enable pin for the 2nd pump
const int vacuumPump2rly4Pin = PA13; //4 IN pin for the 2nd pump

const int pump3valve3rly5Pin = PA4; //5 //Enable pin for the 1st vacuum pump
const int pump4rly6Pin = PA5; //6 //IN pin for the 1st vacuum pump
const int pump5rly7Pin = PA6; //7 //Enable pin for the 2nd vacuum pump
const int pump6rly8Pin = PA7; //8 //IN pin for the 2nd vacuum pump

const int pump7rly9Pin = PA8;//9 //Enable pin for the 3rd pump
const int pump8rly10Pin = PA9; //10 //IN pin for the 3rd pump
const int pump9valve8rly11Pin = PA10; //11 //Enable pin for the 4th pump

// Define the pins for the reaction chambers and centrifuge
const int primaryRxnChamberRly12Pin = PB14; //12 //Relay pin for the primary reaction chamber
const int auxiliaryRxnChamberRly13Pin = PB15; //13 //Relay pin for the auxiliary reaction chamber
const int centrifugeRly14Pin = PC0; //14 //Relay pin for the centrifuge

// Define the buzzer pin
const int buzzerPin = PC1; // Buzzer pin (assuming PC1)


/*// Define pin mappings (D0 to D15 on Nucleo F303RE)
const int pump1rly1Pin = D0;
const int pump2rly2Pin = D1;
const int vacuumPump1rly3Pin = D2; 
const int vacuumPump2rly4Pin = D3; 
const int pump3valve3rly5Pin = D4; 
const int pump4rly6Pin = D5; 
const int pump5rly7Pin = D6; 
const int pump6rly8Pin = D7; 
const int pump7rly9Pin = D8; 
const int pump8rly10Pin = D9; 
const int pump9valve8rly11Pin = D10; 
const int primaryRxnChamberRly12Pin = D11; 
const int auxiliaryRxnChamberRly13Pin = D12; 
const int centrifugeRly14Pin = D13; */

// Define total number of components
const int totalNoOfComponents = 16;

// Define durations (in ms)
const int fillupUEOstorageDuration = 120000;//00
const int prefiltrationDuration = 20000;
const int prefiltrationWaitDuration = 2000;
const int prefiltrRepetitions = 10;
const int prefiltrationEmptyDuration = 40000;
const int acidDrawDuration = 10000;
const int rxnPhz1Duration = 308000;
const int alcoholDrawDuration = 20000;
const int alcoholBlendDuration = 428000;
const int alcoholBlendEmptyDuration = 20000;
const int rxnPhz2Duration = 908000;
const int centrifugeRepetitions = 2;
const int centrifugationSpoolUpTime = 10000;
const int centrifugationHalfTime = 123000; 
const int centrifugationHalfWaitTime = 12000;
const int postFiltrFillUpDuration = 20000;      
const int postFiltrFillUpWaitDuration = 3000;  
const int postFiltrRepetitions = 15;
const int postFiltrationEmptyDuration = 40000; 

void setup() {
  // Initialize GPIO pins as outputs
  pinMode(pump1rly1Pin, OUTPUT);
  pinMode(pump2rly2Pin, OUTPUT);
  //pinMode(vacuumPump1rly3Pin, OUTPUT);
  pinMode(vacuumPump2rly4Pin, OUTPUT);
  pinMode(pump3valve3rly5Pin, OUTPUT);
  pinMode(pump4rly6Pin, OUTPUT);
  pinMode(pump5rly7Pin, OUTPUT);
  pinMode(pump6rly8Pin, OUTPUT);
  pinMode(pump7rly9Pin, OUTPUT);
  pinMode(pump8rly10Pin, OUTPUT);
  pinMode(pump9valve8rly11Pin, OUTPUT);
  pinMode(primaryRxnChamberRly12Pin, OUTPUT);
  pinMode(auxiliaryRxnChamberRly13Pin, OUTPUT);
  pinMode(centrifugeRly14Pin, OUTPUT);

  // Initial states (all off)
  for (int i = 1; i <= totalNoOfComponents; i++) {
    digitalWrite(pump1rly1Pin + i - 1, LOW);
  }

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("All Systems Starting");
}

void loop() {
  Serial.println("Starting UEO recycling...");
  fillupUEOstorageunit();
  prefiltrationStage();
  reactionPhase1();
  auxiliaryReactionChamber();
  reactionPhase2();
  centrifugation();
  postFiltration();
  finalStorageUnit();

  Serial.println("UEO recycled into Fuel Oil...");

  // Final states (all off)
  for (int i = 1; i <= totalNoOfComponents; i++) {
    digitalWrite(pump1rly1Pin + i - 1, LOW);
  }
  Serial.println("All Systems closed");
  delay(2000);
}

// Function to fill the UEO storage unit
void fillupUEOstorageunit() {
  digitalWrite(pump1rly1Pin, HIGH);
  Serial.println("Filling UEO storage...");
  delay(fillupUEOstorageDuration);
  digitalWrite(pump1rly1Pin, LOW);
  Serial.println("UEO storage filled.");
}

// Function for pre-filtration stage
void prefiltrationStage() {
  Serial.println("Starting pre-filtration...");
  //digitalWrite(vacuumPump1rly3Pin, HIGH); 

  for (int i = 0; i < prefiltrRepetitions; i++) {
    digitalWrite(pump2rly2Pin, HIGH);
    delay(prefiltrationDuration);
    digitalWrite(pump2rly2Pin, LOW);
    Serial.println("1 cycle of Pre-Filtration completed.");
    delay(prefiltrationWaitDuration);
  }
  
  //digitalWrite(vacuumPump1rly3Pin, LOW); 
  Serial.println("Pre-filtration completed...");
}

// Function for reaction phase 1
void reactionPhase1() {
  Serial.println("Drawing chemicals for reaction phase 1...");
  
  digitalWrite(pump3valve3rly5Pin, HIGH);
  delay(prefiltrationEmptyDuration); // Delay for emptying pre-filtration unit
  digitalWrite(pump3valve3rly5Pin, LOW);

  Serial.println("Filtered Oil collected.");

  Serial.println("Start drawing Acid.");
  
  digitalWrite(pump4rly6Pin, HIGH);
  delay(acidDrawDuration); // Run pump 4 for acid draw
  digitalWrite(pump4rly6Pin, LOW);
  
  Serial.println("Acid drawn successfully.");
  
  Serial.println("Starting Reaction phase 1 ");

  digitalWrite(primaryRxnChamberRly12Pin, HIGH);
  delay(rxnPhz1Duration); 
  digitalWrite(primaryRxnChamberRly12Pin, LOW);

  Serial.println("Reaction phase 1 completed.");
}

// Function for auxiliary reaction chamber
void auxiliaryReactionChamber() {
  Serial.println("Chemical Draw for Auxiliary Reaction phase...");
  
  delay(2000);
  
  Serial.println("Start drawing Alcohol.");

  digitalWrite(pump5rly7Pin, HIGH);
  delay(alcoholDrawDuration); // Draw alcohol
  digitalWrite(pump5rly7Pin, LOW);

  Serial.println("Alcohol drawn successfully.");

  Serial.println("Starting Auxiliary Reaction phase...");
  
  digitalWrite(auxiliaryRxnChamberRly13Pin, HIGH);
  delay(alcoholBlendDuration); 
  digitalWrite(auxiliaryRxnChamberRly13Pin, LOW);
  
  Serial.println("Auxiliary Reaction phase completed.");
}

// Function for reaction phase 2
void reactionPhase2() {
  Serial.println("Drawing chemicals for reaction phase 1...");
  
  delay(2000);
  
  Serial.println("Start drawing Alcohol blend.");

  digitalWrite(pump6rly8Pin, HIGH); // Empty blend
  delay(alcoholBlendEmptyDuration);
  digitalWrite(pump6rly8Pin, LOW);

  Serial.println("Alcohol Blend drawn successfully.");

  Serial.println("Starting reaction phase 2...");
  
  digitalWrite(primaryRxnChamberRly12Pin, HIGH);
  delay(rxnPhz2Duration); // Run for reaction phase 2
  digitalWrite(primaryRxnChamberRly12Pin, LOW);

  Serial.println("Reaction phase 2 completed.");
}

// Other functions as needed...
// Function for centrifugation
void centrifugation() {
  Serial.println("Starting centrifugation phase...");
  delay(2000);

  for (int i = 0; i < centrifugeRepetitions; i++) {
    Serial.println("Spooling Up Centrifuge...");
 
    digitalWrite(centrifugeRly14Pin, HIGH);  // Start centrifugation
    delay(centrifugationSpoolUpTime);  // Wait half the duration

    Serial.println("Fuel Mixture entering Centrifuge");
    digitalWrite(pump7rly9Pin, HIGH); // Activate fuel-mix epmtying
    //delay(fuelMixEmptyDuration); // Run for half the duration
    
    delay(centrifugationHalfTime);  // Wait for the remaining duration
    digitalWrite(centrifugeRly14Pin, LOW);  // Stop centrifugation
    digitalWrite(pump7rly9Pin, LOW);

    Serial.println("1 Centrifuge cycle Completed");
    
    delay(centrifugationHalfWaitTime);  // Wait for the remaining du
  }

  Serial.println("Centrifugation completed.");
  delay(2000);
}

// Function for post-filtration
void postFiltration() {
  Serial.println("Starting post-filtration phase...");
 
  delay(2000);

  digitalWrite(vacuumPump2rly4Pin, HIGH);
  
  for (int i = 0; i < postFiltrRepetitions; i++) {
    digitalWrite(pump8rly10Pin, HIGH);
    delay(postFiltrFillUpDuration);
    digitalWrite(pump8rly10Pin, LOW);
    
    Serial.println("1 cycle of Post-Filtration completed.");
 
    delay(postFiltrFillUpWaitDuration); // Wait time
  }
  
  digitalWrite(vacuumPump2rly4Pin, LOW);
  
  Serial.println("Post-filtration completed.");
  delay(2000);
}

// Function for final storage unit
void finalStorageUnit() {
  Serial.println("Transferring recycled oil to final storage...");
 
  digitalWrite(pump9valve8rly11Pin, HIGH); // using pump 9 for final storage
  //digitalWrite(valve8rly13Pin, HIGH); // Open valve 3
  delay(postFiltrationEmptyDuration); // Fill final storage
  digitalWrite(pump9valve8rly11Pin, LOW);
  //digitalWrite(valve8rly13Pin, HIGH); // Close valve 3

  Serial.println("Recycled oil stored in Final Storage unit.");
 
  delay(2000);
}