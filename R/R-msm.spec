%global packname msm
%global packrel 1

Name:             R-%{packname}
Version:          0.8.2
Release:          1%{?dist}
Source0:          ftp://cran.r-project.org/pub/R/contrib/main/%{packname}_%{version}.tar.gz
License:          GPLv2
URL:              http://cran.r-project.org/src/contrib
Group:            Applications/Engineering
Summary:          Multi-state Markov and hidden Markov models in continuous time
BuildRequires:    R-devel, tetex-latex, R-mvtnorm
BuildRoot:        %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArch:        noarch
Requires(post):   R
Requires(postun): R
Requires:         R

%description
Functions for fitting general continuous-time Markov and hidden Markov
multi-state models to longitudinal data.  Both Markov transition rates
and the hidden Markov output process can be modelled in terms of
covariates.  A variety of observation schemes are supported, including
processes observed at arbitrary times, completely-observed processes,
and censored states.

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
#%%doc %{_datadir}/R/library/%{packname}/latex
#%%doc %{_datadir}/R/library/%{packname}/doc
#%%doc %{_datadir}/R/library/%{packname}/html
%doc %{_datadir}/R/library/%{packname}/man
%doc %{_datadir}/R/library/%{packname}/DESCRIPTION
#%%doc %{_datadir}/R/library/%{packname}/NEWS
#%%{_datadir}/R/library/%{packname}/CONTENTS
#%%{_datadir}/R/library/%{packname}/INDEX
%{_datadir}/R/library/%{packname}/NAMESPACE
#%%{_datadir}/R/library/%{packname}/Meta
%{_datadir}/R/library/%{packname}/R
#%%{_datadir}/R/library/%{packname}/R-ex
#%%{_datadir}/R/library/%{packname}/help

%changelog
* Sun May 03 2009 Denis Arnaud <denis.arnaud_fedora@m4x.org> 0.0-1
- Initial package creation
