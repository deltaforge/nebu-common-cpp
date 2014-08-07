Name:           libnebu-common
Version:        0.1.0
Release:        1%{?dist}
Summary:        Common functionality for Nebu-based applications

License:        Pending
URL:            https://github.com/deltaforge
Source0:        %{name}-%{version}.tar.gz

BuildRequires:	tinyxml2-devel >= 2.1.0
Requires:	    tinyxml2 >= 2.1.0

%description
Libnebu-common is a C++ library providing common functionality for applications
that use Nebu. The main feature is easy access to REST calls to the
middleware API.

%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.


%prep
%autosetup -n %{name}-%{version}

./bootstrap


%build
%configure
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}
rm -f %{buildroot}%{_libdir}/*.a %{buildroot}%{_libdir}/*.la


%files
%defattr(-,root,root)
%doc
%{_libdir}/*.so.*


%files devel
%defattr(-,root,root)
%doc
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/%{name}.pc


%changelog
* Wed Jul 9 2014 Tim Hegeman <tim.m.hegeman@gmail.com> 0.1.0-1
- Inital version of the package

