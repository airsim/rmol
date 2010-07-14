%define packname	mvtnorm
%define packrel		9

Summary:	Multivariate normal and T distribution R Package
Name:		R-%{packname}
Version:	0.9
Release:	9%{?dist}
License:	GPLv2
Group:		Applications/Engineering
Source0:	http://cran.r-project.org/src/contrib/%{packname}_%{version}-%{packrel}.tar.gz
URL:		http://cran.r-project.org/web/packages/mvtnorm/index.html
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:	R-devel, tex(latex), gcc-gfortran
Requires(post):		R
Requires(postun):	R
Requires:		R


%description
This R package computes multivariate normal and t probabilities, quantiles
and densities.


%prep
%setup -q -c -n %{packname}


%build


%install
rm -rf %{buildroot}
mkdir -p $RPM_BUILD_ROOT%{_libdir}/R/library
%{_bindir}/R CMD INSTALL %{packname} -l %{buildroot}%{_libdir}/R/library
# Clean up in advance of check
test -d %{packname}/src && (cd %{packname}/src; rm -f *.o *.so)
rm -rf %{buildroot}%{_libdir}/R/library/R.css


%check
%{_bindir}/R CMD check %{packname}


%clean
rm -rf %{buildroot}


%post
%{_R_make_search_index}


%postun
%{_R_make_search_index}


%files
%defattr(-, root, root, -)
%dir %{_libdir}/R/library/%{packname}
%doc %{_libdir}/R/library/%{packname}/doc
%doc %{_libdir}/R/library/%{packname}/html
%doc %{_libdir}/R/library/%{packname}/CHANGES
%doc %{_libdir}/R/library/%{packname}/CITATION
%doc %{_libdir}/R/library/%{packname}/DESCRIPTION
%doc %{_libdir}/R/library/%{packname}/NEWS
%{_libdir}/R/library/%{packname}/INDEX
%{_libdir}/R/library/%{packname}/NAMESPACE
%{_libdir}/R/library/%{packname}/Meta
%{_libdir}/R/library/%{packname}/R
%{_libdir}/R/library/%{packname}/help
%{_libdir}/R/library/%{packname}/libs


%changelog
* Mon Jun 21 2010 Orion Poplawski <orion@cora.nwra.com> - 0.9-9
- Update to 0.9-9

* Thu Nov 19 2009 Orion Poplawski <orion@cora.nwra.com> - 0.9-8.1
- Update to 0.9-8
- Update spec for R 2.10.0 (fixes FTBFS bug #539041)

* Fri Jul 24 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.9-8
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Tue Jul 14 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> - 0.9-7
- Update to 0.9-7

* Mon Feb 23 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.9-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_11_Mass_Rebuild

* Thu Sep 4 2008 Orion Poplawski <orion@cora.nwra.com> - 0.9-1
- Update to 0.9-2

* Sat Feb  9 2008 Orion Poplawski <orion@cora.nwra.com> - 0.8-4
- Rebuild for gcc 3.4

* Thu Aug 23 2007 Orion Poplawski <orion@cora.nwra.com> - 0.8-3
- Update license tag to GPLv2
- Rebuild for ppc32

* Tue Jul 24 2007 Orion Poplawski <orion@cora.nwra.com> - 0.8-2
- Update to 0.8-1, fixes test

* Mon Jul 23 2007 Orion Poplawski <orion@cora.nwra.com> - 0.8-1
- Update to 0.8-0

* Wed Jul 11 2007 Orion Poplawski <orion@cora.nwra.com> - 0.7-2
- Comply with R packaging guidelines

* Mon Mar 19 2007 Orion Poplawski <orion@cora.nwra.com> - 0.7-1
- Initial package

