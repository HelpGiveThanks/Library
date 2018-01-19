January 11, 2018 18:53:58 Library.fmp12 - gotoHelpGiveThanksWebsite -1-
librarySetup: gotoHelpGiveThanksWebsite
#
#Close all solutions window after selecting website.
If [ $$otherApps = 1 ]
Set Variable [ $$otherApps ]
Close Window [ Name: "All Solutions"; Current file ]
Open URL [ "https://helpgivethanks.github.io/" ]
[ No dialog ]
End If
