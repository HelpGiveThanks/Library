July 20, 2018 17:26:28 Library.fmp12 - gotoHelpGiveThanksWebsite -1-
librarySetup: gotoHelpGiveThanksWebsite
#
#Close all solutions window after selecting website.
If [ $$otherApps = 1 ]
Set Variable [ $$otherApps ]
Close Window [ Name: "All Apps"; Current file ]
Open URL [ "https://helpgivethanks.github.io/" ]
[ No dialog ]
Halt Script
End If
