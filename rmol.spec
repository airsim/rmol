#
%global mydocs __tmp_docdir
#
Name:           rmol
Version:        0.24.0
Release:        1%{?dist}

Summary:        C++ library of Revenue Management and Optimisation classes and functions

Group:          System Environment/Libraries 
License:        LGPLv2+
URL:            http://%{name}.sourceforge.net
Source0:        http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.bz2
BuildRoot:      %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:  cmake, python-devel
BuildRequires:  boost-devel, gsl-devel, soci-mysql-devel, zeromq-devel
BuildRequires:  readline-devel, stdair-devel


%description
%{name} is a C++ library of Revenue Management and Optimisation classes 
and functions. Typically, that library may be used by service providers
(e.g., airlines offering flight seats, hotels offering rooms, rental car
companies offering rental days, broadcasting company offering advertisement 
slots, theaters offering seats, etc.) to help in optimising their revenues from
seat capacities.
Most of the algorithms implemented are public and documented in the following
book:
The Theory and practice of Revenue Management, by Kalyan T. Talluri and
Garrett J. van Ryzin, Kluwer Academic Publishers, 2004, ISBN 1-4020-7701-7

%{name} makes an extensive use of existing open-source libraries for
increased functionality, speed and accuracy. In particular the
Boost (C++ Standard Extensions: http://www.boost.org) library is used.

Install the %{name} package if you need a library of basic C++ objects
for Airline Revenue Management (RM), mainly for simulation purpose.

%package        devel
Summary:        Header files, libraries and development helper tools for %{name}
Group:          Development/Libraries
Requires:       %{name}%{?_isa} = %{version}-%{release}
Requires:       pkgconfig
Requires(post): info
Requires(preun): info

%description    devel
This package contains the header files, shared libraries and
development helper tools for %{name}. If you would like to develop
programs using %{name}, you will need to install %{name}-devel.

%package        doc
Summary:        HTML documentation for the %{name} library
Group:          Documentation
%{?fedora:BuildArch:      noarch}
BuildRequires:  tex(latex)
BuildRequires:  doxygen, ghostscript

%description    doc
This package contains HTML pages, as well as a PDF reference manual,
for %{name}. All that documentation is generated thanks to Doxygen
(http://doxygen.org). The content is the same as what can be browsed
online (http://%{name}.org).


%prep
%setup -q


%build
%configure --disable-static
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%find_lang %{name}

# Remove unpackaged files from the buildroot
rm -f $RPM_BUILD_ROOT%{_infodir}/dir

mkdir -p %{mydocs}
mv $RPM_BUILD_ROOT%{_docdir}/%{name}-%{version}/html %{mydocs}

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%post devel
/sbin/install-info %{_infodir}/%{name}-ref.info.* %{_infodir}/dir || :

%preun devel 
if [ "$1" = 0 ]; then
   /sbin/install-info --delete %{_infodir}/%{name}-ref.info.* %{_infodir}/dir || :
fi

%files -f %{name}.lang
%defattr(-,root,root,-)
%doc AUTHORS ChangeLog COPYING NEWS README
%{_bindir}/%{name}
%{_libdir}/lib%{name}.so.*
%{_mandir}/man1/%{name}.1.*

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}
%{_bindir}/%{name}-config
%{_libdir}/lib%{name}.so
%{_libdir}/pkgconfig/%{name}.pc
%{_datadir}/aclocal/%{name}.m4
%{_infodir}/%{name}-ref.info.*
%dir %{_datadir}/%{name}
%{_datadir}/%{name}/CMake
%{_mandir}/man1/%{name}-config.1.*
%{_mandir}/man3/%{name}-library.3.*

%files doc
%defattr(-,root,root,-)
%doc %{mydocs}/html
%doc COPYING


%changelog
* Tue Aug 30 2011 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.24.0-1
- Upstream integration

* Tue Sep 15 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.23.0-1
- Upstream integration

* Mon May 11 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.22.0-1
- Upstream integration

* Sun May 10 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.21.0-3
- Removed dependencies on specific versions (for EL 5)

* Sat May 09 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.21.0-2
- Removed dependencies on specific versions (for EL 5)

* Mon May 04 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.21.0-1
- Upstream integration

* Sun May 03 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.20.0-3
- Added dependency on libicu for Boost 1.37 (Fedora 11)

* Sun May 03 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.20.0-2
- Added dependency on libicu-devel for Boost 1.37 (Fedora 11)

* Sun May 03 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.20.0-1
- Upstream integration

* Sun Mar 25 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.19.0-1
- RPM release for Fedora 10

* Wed Mar  4 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.18.0-1
- Second RPM release
