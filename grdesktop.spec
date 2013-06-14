Summary: A gtk2 frontend for rdesktop
Name: grdesktop
Version: 0.22
Release: 1
Group: Internet
License: GPL
Source0: %{name}-%{version}.tar.gz
Source1: %{name}-%{version}.tar.gz.gpg
Source2: %{name}-%{version}.tar.gz.md5
BuildRoot: %{_tmppath}/%{name}-%{version}-root
URL: http://www.nongnu.org/grdesktop/
#Prefix: /
Requires: rdesktop


%description
grdesktop is a frontend, written in C using the GTK+ 2 toolkit, for the remote desktop client (rdesktop).
It can save several connections (including their options), and browse the network for available terminal servers.

%prep
%setup


%build
%configure
make

%install
%makeinstall

#Install application link for X-Windows
install -d %{buildroot}/etc/X11/applnk/Internet
echo -e "[Desktop Entry]
Name=%name
Comment=rdesktop frontend
Exec=grdesktop
#Icon=%name.xpm
Terminal=0
Type=Application" > %{buildroot}/etc/X11/applnk/Internet/"grdesktop".desktop

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc ABOUT-NLS
%doc AUTHORS
%doc COPYING
%doc ChangeLog
%doc INSTALL
%doc NEWS
%doc README
%doc TODO
%doc doc
%{_bindir}/grdesktop
%{_datadir}/locale/de/LC_MESSAGES/grdesktop.mo
%{_datadir}/locale/fr/LC_MESSAGES/grdesktop.mo
%{_datadir}/man/man1/grdesktop.1.gz
%{_datadir}/pixmaps/grdesktop/*.gif
%{_datadir}/pixmaps/grdesktop/*.png
%{_datadir}/pixmaps/grdesktop/*.xpm
/etc/X11/applnk/Internet/grdesktop.desktop

%changelog
* Sun Nov 9 2003 tsauter
- version upgrade

* Tue Nov 12 2002 Che
- version upgrade
- prettyfied it a bit :P

* Fri Nov 01 2002 Che
- initial rpm release
