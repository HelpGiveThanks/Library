January 17, 2018 11:37:11 Library.fmp12 - haltShareScript -1-
learn: haltShareScript
#
#Stop share script.
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Name: "Share"; Current file ]
Install Menu Set [ “HGT” ]
Halt Script
