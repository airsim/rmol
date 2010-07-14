%global packname RM2

Name:             R-%{packname}
Version:          0.0
Release:          5%{?dist}
Source0:          ftp://cran.r-project.org/pub/R/contrib/main/%{packname}_%{version}.tar.gz
License:          GPLv3+
URL:              http://cran.r-project.org/web/packages/RM2/
Group:            Applications/Engineering
Summary:          Revenue Management and Pricing for R
BuildRequires:    R-devel, tetex-latex, R-msm, R-mvtnorm
BuildRoot:        %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArch:        noarch
Requires(post):   R
Requires(postun): R
Requires:         R, R-msm, R-mvtnorm

%description
RM2 is a simple package that implements functions 
used in revenue management and pricing environments.

%prep
%setup -q -c -n %{packname}

%build

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{_datadir}/R/library
%{_bindir}/R CMD INSTALL -l $RPM_BUILD_ROOT%{_datadir}/R/library %{packname}
test -d %{packname}/src && (cd %{packname}/src; rm -f *.o *.so)
rm -rf $RPM_BUILD_ROOT%{_datadir}/R/library/R.css

%check
%{_bindir}/R CMD check %{packname}

%clean
rm -rf $RPM_BUILD_ROOT

%post
%{_R_make_search_index}

%postun
%{_R_make_search_index}

%files
%defattr(-, root, root, -)
%dir %{_datadir}/R/library/%{packname}
%doc %{_datadir}/R/library/%{packname}/html
%doc %{_datadir}/R/library/%{packname}/DESCRIPTION
%{_datadir}/R/library/%{packname}/INDEX
%{_datadir}/R/library/%{packname}/NAMESPACE
%{_datadir}/R/library/%{packname}/Meta
%{_datadir}/R/library/%{packname}/R
%{_datadir}/R/library/%{packname}/help

%changelog
* Tue Jul 14 2010 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.0-5
- Update spec for R 2.10.0 (fixes the same bug as FTBFS bug #539041)

* Tue Jul 07 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.0-4
- Removed commented lines and unused variables/macros

* Mon Jul 06 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.0-3
- No longer use packrel for RPM release version, and updated 
  the license from GPLv3 to GPLv3+

* Sat Jun 27 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.0-2
- Integrated the dependency on R-msm and R-mvtnorm

* Sun May 03 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.0-1
- Initial package creation

