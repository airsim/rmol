#
%global mydocs __tmp_docdir
#
Name:           stdair
Version:        99.99.99
Release:        1%{?dist}

Summary:        C++ Standard Airline IT Object Library

Group:          System Environment/Libraries 
License:        LGPLv2
URL:            http://sourceforge.net/projects/%{name}/
Source0:        http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.bz2
%{?el5:BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)}

BuildRequires:  boost-devel
BuildRequires:  soci-mysql-devel
# When the extracc package will be approved, uncomment the following line
# (see https://bugzilla.redhat.com/show_bug.cgi?id=616881 for more details)
#BuildRequires:  extracc-devel
BuildRequires:  cppunit-devel


%description
%{name} aims at providing a clean API, and the corresponding C++
implementation, for the basis of Airline IT Business Object Model (BOM),
that is, to be used by several other Open Source projects, such as RMOL, 
Air-Sched, Travel-CCM, OpenTREP, etc.

Install the %{name} package if you need a library for Airline IT Standard 
C++ fundaments.

%package        devel
Summary:        Header files, libraries and development documentation for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       pkgconfig

%description    devel
This package contains the header files, static libraries and
development documentation for %{name}. If you would like to develop
programs using %{name}, you will need to install %{name}-devel.

%package doc
Summary:        HTML documentation for the %{name} library
Group:          Documentation
%{?fedora:BuildArch:      noarch}
BuildRequires:  tex(latex)
BuildRequires:  doxygen, ghostscript

%description doc
This package contains the documentation in the HTML format of the %{name}
library. The documentation is the same as at the %{name} web page.


%prep
%setup -q
# The INSTALL package is not relevant for RPM package users
# (e.g., see https://bugzilla.redhat.com/show_bug.cgi?id=489233#c4)
rm -f INSTALL
# Fix some permissions and formats
chmod -x AUTHORS ChangeLog COPYING NEWS README
find . -type f -name '*.[hc]pp' -exec chmod 644 {} \;


%build
%configure --disable-static
make %{?_smp_mflags}

%install
# On Fedora, the BuildRoot is automatically cleaned. Which is not the case for
# RedHat. See: https://fedoraproject.org/wiki/Packaging/Guidelines#BuildRoot_tag
%{?rhel:rm -rf $RPM_BUILD_ROOT}

make install DESTDIR=$RPM_BUILD_ROOT INSTALL="install -p"

# Remove unpackaged files from the buildroot
rm -f $RPM_BUILD_ROOT%{_libdir}/lib%{name}.la
# When the extracc package will be approved, the following line has to be removed
rm -f $RPM_BUILD_ROOT%{_libdir}/libextracppunit.la

mkdir -p %{mydocs}
mv $RPM_BUILD_ROOT%{_docdir}/%{name}-%{version}/html %{mydocs}

%if 0%{?rhel}
%clean
rm -rf $RPM_BUILD_ROOT
%endif

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%doc AUTHORS ChangeLog COPYING NEWS README
%{_bindir}/%{name}
%{_libdir}/lib*.so.*
%{_mandir}/man1/%{name}.1.*

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}
%{_includedir}/extracppunit
%{_bindir}/%{name}-config
%{_libdir}/lib%{name}.so
%{_libdir}/libextracppunit.so
%{_libdir}/pkgconfig/%{name}.pc
%{_datadir}/aclocal/%{name}.m4
%{_mandir}/man1/%{name}-config.1.*
%{_mandir}/man3/%{name}-library.3.*

%files doc
%defattr(-,root,root,-)
%doc %{mydocs}/html
%doc COPYING


%changelog
* Sun Aug 30 2010 Son Nguyen Kim <nguyenkims@gmail.com> 99.99.99-1
- Upstream update

* Sun Aug 29 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.3.0-1
- Upstream update

* Wed Jul 13 2010 Son Nguyen Kim <nguyenkims@gmail.com> 0.1.0-1
- First RPM release

