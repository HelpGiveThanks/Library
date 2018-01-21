January 21, 2018 12:28:37 Library.fmp12 - referenceLoop -1-
dataCleanUpScripts: referenceLoop
#
#Use this script to change some information in all
#records currently found. Useful for when you make
#an error covering many records to correct the error.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Record/Request/Page
[ First ]
Loop
// Set Field [ reference::kkeywordOther; 6152012170316227 & ¶ &
426201211190634 & ¶ &
6202012153813240 & ¶ &
6202012165313251 & ¶ &
10212011022440584 & ¶ &
6092012194220193 & ¶ &
8312012200828513 & ¶ &
8112011135327306 & ¶ &
5262013013530620 & ¶ &
120420111059441036 & ¶ &
9132011003103394 & ¶ ]
// Set Field [ reference::kkeywordPrimary; 10142013154511774 ]
// Set Field [ reference::OtherKeyWords; "brain and military, brain and the law, causes and conditions, cognitive control,
epidemics, evolution, illusion (rational), mental illness, neuropsychiatry, suicide, volition" ]
// Set Field [ reference::kfileLocation; 8162011225605315 ]
// Set Field [ reference::kfolderpath; 5312012152200119 ]
// Set Variable [ $isON; Value:reference::kisON ]
// Set Variable [ $isWHAT; Value:reference::kisWhat ]
Set Field [ reference::kisON; 420201300192711 ]
Set Field [ reference::kisWhat; 505201316131590 ]
// Set Field [ reference::kcopyrightHolder; 6022012160448133 ]
// Set Field [ reference::referenceNodes; "Cold Spring Harbor Laboratory" ]
// Set Field [ reference::kpublication; "" ]
// Set Field [ reference::kpublisher; 5102013023502585 ]
// Set Field [ reference::GovernmentDocInfo; "Series speakers are from the UCSF Center for Obesity Assessment, Study and
Treatment" ]
// Set Field [ reference::kpublication; 6032012182212144 ]
// Set Field [ reference::CopyrightYear; "" ]
// Set Field [ reference::publicationYearOrStuffOrderNumber; "" ]
// Set Field [ reference::incomplete; "" ]
// Set Field [ reference::kCopyright; "8102011220941282" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadCitation ]
