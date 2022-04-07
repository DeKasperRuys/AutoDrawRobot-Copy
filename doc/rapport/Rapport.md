**Bluetooth**

**Coördinaten beweging**

**Motor**

**NineDof**

Het aanroepen van de juiste data met de 9DoF-stick. Er waren meerdere mogelijkheden om hoeken te kunnen bepalen. Heading gaf te onnauwkeurige data dus kon niet gebruikt worden. Er werd dus gekozen voor de graden per seconden te gebruiken van de gyroscoop op de 9DoF. Oorspronkelijk konden we ook de ultrasone sensors gebruiken als stappenteller om te bepalen hoe ver de robot is gedraaid, maar hebben we uiteindelijk gekozen voor de 9DoF met de gedachte dat dit minder code zou vragen door gebruik van de deg/s om te zetten naar graden bewogen.
Problemen met 9DoF was eerst en vooral het kiezen van welke data er gebruikt ging worden. Heading was te onnauwkeurig en met graden/s leek er een beter resultaat te zijn. In de code apart kon de 9DoF zeer juiste resultaten geven. Het breadboard draaide een mooie 90 graden. Met het samenvoegen van andere constante lezingen van de ultrasone sensors kwamen er fouten en bleek de robot niet mooi 90 graden meer te draaien. De snelheid van robot deed er ook toe want als er te snel werdt gedraaid kon de robot minder data lezen.

**Ultrasone Sensor**


**EindePresentatie**

https://docs.google.com/presentation/d/15tW4AH5WiXyiAm9hUx1njehOJ8_N4_V-md0mN8ba224/edit?usp=sharing
