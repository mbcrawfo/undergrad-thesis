\newcommand{\asuthesisupdate}{2004/02/07}
\newcommand{\asuthesisversion}{v1.1}

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{asu}

\newcommand{\@thesisptsz}{}
\newcommand{\@thesisside}{}
\newcommand{\@thesisopen}{}
\newcommand{\@thesislnsp}{}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{report}}
\ProcessOptions
\LoadClass[\@thesisptsz,\@thesisside,\@thesisopen]{report}

\newcommand{\degree}[1]{\ifx\empty#1\else\gdef\@degree{#1}\fi}
\newcommand{\department}[1]{\ifx\empty#1\else\gdef\@department{#1}\fi}
\newcommand{\gradmonth}[1]{\ifx\empty#1\else\gdef\@gradmonth{#1}\fi}
\newcommand{\gradyear}[1]{\ifx\empty#1\else\gdef\@gradyear{#1}\fi}
\newcommand{\thesischair}[1]{\ifx\empty#1\else\gdef\@thesischair{#1}\fi}
\newcommand{\thesismemberone}[1]{\ifx\empty#1\else\gdef\@thesismemberone{#1}\fi}
\newcommand{\thesismembertwo}[1]{\ifx\empty#1\else\gdef\@thesismembertwo{#1}\fi}
\newcommand{\deptchair}[1]{\ifx\empty#1\else\gdef\@deptchair{#1}\fi}
\newcommand{\dean}[1]{\ifx\empty#1\else\gdef\@dean{#1}\fi}
\renewcommand{\author}[1]{\ifx\empty#1\else\gdef\@author{#1}\fi}
\renewcommand{\title}[1]{\ifx\empty#1\else\gdef\@title{#1}\fi}

\newcommand{\newlinestretch}[1]{\renewcommand{\baselinestretch}{#1}\normalsize}

\newenvironment{preliminary}
  {\pagestyle{plain}\pagenumbering{roman}}
  {\cleardoublepage\pagenumbering{arabic}}

\renewcommand{\maketitle}{
   \begin{titlepage}
   \begin{center}
      {\@title} \\[15ex]
      \newlinestretch{2}
      by \\
      {\@author} \\[6ex]
      Honors Thesis \\
      Appalachian State University \\
      Submitted to the Department of Computer Science \\
      in partial fulfillment of the requirements for the degree of \\
      {\@degree} \\[12ex]
      {\@gradmonth} {\@gradyear} \\ [4ex]
   \end{center}
   \begin{flushright}
   APPROVED BY: \\ [6ex]
   \underline{\hspace{3in}} \\
   {\@thesischair}, Thesis Project Director \\ [6ex]
   \underline{\hspace{3in}} \\
   {\@thesismemberone}, Second Reader \\ [6ex]
   \underline{\hspace{3in}} \\
   {\@thesismembertwo}, Departmental Honors Director \\ [6ex]
   \underline{\hspace{3in}} \\
   {\@deptchair}, Chair, Computer Science \\
   \end{flushright}
   \setcounter{page}{1}
   \end{titlepage}
   \setcounter{page}{2}
   %\end{right}
}

\newcommand{\makeapproval}{
   \thispagestyle{empty}
   \vspace*{0.5in}
   \begin{center}
      {\@title} \\
      \vspace{1.5in}
      \newlinestretch{2}
      A Thesis \\
      by \\
      {\@author} \\
      {\@gradmonth} {\@gradyear}
   \end{center}
   \vspace{1cm}
   APPROVED BY: \\ [2ex]
   \underline{\hspace{2.7in}} \\
   {\@thesischair} \\
   Chairperson, Thesis Committee \\[2ex]
   \underline{\hspace{2.7in}} \\
   {\@thesismemberone} \\
   Member, Thesis Committee \\[2ex]
   \underline{\hspace{2.7in}} \\
   {\@thesismembertwo} \\
   Member, Thesis Committee \\[2ex]
   \underline{\hspace{2.7in}} \\
   {\@deptchair} \\
   Chairperson, {\@department} \\[2ex]
   \underline{\hspace{2.7in}} \\
   {\@dean} \\
   Dean of Graduate Studies and Research
   \newpage
}

\newcommand{\makecopyright}{
    \vspace*{3.5in}
    \begin{center}
    Copyright{\copyright} {\@author} {\@gradyear}\\
    All Rights Reserved
    \end{center}
    \setcounter{page}{2}
    \newpage
}

\renewenvironment{abstract}{
   \vspace*{0.5in}
   \begin{center}
      ABSTRACT \\[2ex]
      \newlinestretch{2}
      {\@title}.\\
      ({\@gradmonth} {\@gradyear})\\
      {\@author}, Appalachian State University\\
      Appalachian State University \\
      Thesis Chairperson:  {\@thesischair}
   \end{center}
   \newlinestretch{2}
}{\par\newpage}

\newenvironment{acknowledgement}{
   \vspace*{0.5in}
   \begin{center}
      ACKNOWLEDGEMENTS \\[2ex]
      \newlinestretch{2}
   \end{center}
   \newlinestretch{2}
}{\par\newpage}

\newenvironment{dedication}{
   \vspace*{0.5in}
   \newlinestretch{2}
}{\par\newpage}

%
%  PAGE STYLE
%
\newcommand{\ps@asu}{%
   \renewcommand{\@oddhead}{%
      \begin{minipage}{\textwidth}\normalfont
          \hfill \thepage
      \end{minipage}}
   \renewcommand{\@evenhead}{\@oddhead}
   \renewcommand{\@oddfoot}{}
   \renewcommand{\@evenfoot}{}
}
\pagestyle{asu}
\setlength{\parindent}{0.5in}
\setcounter{secnumdepth}{1}
\setcounter{tocdepth}{1}


%
%  MARGINS
%
%  Sets margins to 1 1/2" left margin and 1" everywhere else.
%

\usepackage[top=1in, bottom=1in, left=1.25in, right=1in]{geometry}




%\setlength{\voffset}{-1in}
%\setlength{\hoffset}{-1in}

%\setlength{\textheight}{\paperheight}
%\setlength{\textwidth}{\paperwidth}

%\addtolength{\textheight}{-2in}
%\setlength{\topmargin}{1in}
%\setlength{\headsep}{.5in}
%\setlength{\footskip}{.5in}

%\addtolength{\textwidth}{-2.5in}
%\setlength{\oddsidemargin}{1in}
%\setlength{\evensidemargin}{1in}
%\setlength{\marginparwidth}{.75in}
%\setlength{\marginparsep}{.125in}

%\flushbottom
