January 21, 2018 11:10:25 Library.fmp12 - CHUNK_insertPageNumbersBackOnePage -1-
test: report: print: CHUNK_insertPageNumbersbackOnePage
Select Window [ Name: "Report"; Current file ]
Go to Record/Request/Page
[ Previous ]
Set Variable [ $page; Value:Get ( PageNumber ) ]
Set Field [ TEMP::pageNumber; $page ]
Select Window [ Name: "Numbers"; Current file ]
