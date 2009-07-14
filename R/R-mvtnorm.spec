%define packname mvtnorm
%define packrel  2

Summary:	Multivariate normal and T distribution R Package
Name:		R-%{packname}
Version:	0.9
Release:	2%{?dist}
License:	GPLv2
Group:		Applications/Engineering
Source0:	http://cran.r-project.org/src/contrib/%{packname}_%{version}-%{packrel}.tar.gz
URL:		http://cran.r-project.org/contrib/main/Descriptions/mvtnorm.html
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:	R-devel, tetex-latex, gcc-gfortran
Requires(post):   R
Requires(postun): R
Requires:         R


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
%doc %{_libdir}/R/library/%{packname}/latex
%doc %{_libdir}/R/library/%{packname}/doc
%doc %{_libdir}/R/library/%{packname}/html
%doc %{_libdir}/R/library/%{packname}/man
%doc %{_libdir}/R/library/%{packname}/CHANGES
%doc %{_libdir}/R/library/%{packname}/DESCRIPTION
%{_libdir}/R/library/%{packname}/CONTENTS
%{_libdir}/R/library/%{packname}/INDEX
%{_libdir}/R/library/%{packname}/NAMESPACE
%{_libdir}/R/library/%{packname}/Meta
%{_libdir}/R/library/%{packname}/R
%{_libdir}/R/library/%{packname}/R-ex
%{_libdir}/R/library/%{packname}/help
%{_libdir}/R/library/%{packname}/libs


%changelog
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
